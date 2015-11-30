var express = require( 'express' );
var bodyParser = require( 'body-parser' );
var _ = require( 'lodash' );
var sh = require( 'execSync' );
var Promise = require( 'bluebird' );
var $ = function( obj ) {
    return Promise.promisifyAll( obj, {
        filter: function() { return true; }
    });
};
var fs = $( require( 'fs' ) );
var path = require( 'path' );
var app = express();

app.use(
    function crossOrigin( req, res, next ) {
        res.header( 'Access-Control-Allow-Origin', '*' );
        res.header( 'Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, Authorization, Accept' );
        res.header( 'Access-Control-Allow-Methods', 'OPTIONS, POST, GET, PUT, DELETE' );
        return next();
    }
);
app.use( bodyParser.urlencoded( { extended: true } ) );
app.use( bodyParser.json() );

app.post( '/write', function( req, res, next ) {
    var program = req.body.program;
    program = program.split( '\n' ).map( function( line ) {
        return '        ' + line;
    }).join( '\n' );
    var sketchPath = path.join( __dirname, 'src', 'sketch.ino' );
    var source;

    fs.readFileAsync( sketchPath, 'utf8' )
    .then( function( contents ) {
        source = contents = contents.replace( /\/\/BEGIN[\s\S]*\/\/END/m, '//BEGIN\n' + program + '\n        //END' );

        return fs.writeFileAsync( sketchPath, contents, 'utf8' );
    })
    .then( function() {
        var result = sh.exec( 'ino build' );
        res.sendStatus( result.code === 0 ? 200 : 500 );
    })
    .catch( function( err ) {
        res.sendStatus( 500 );
    });
});

app.post( '/upload', function( req, res, next ) {
    var result = sh.exec( 'ino upload' );
    res.sendStatus( result.code === 0 ? 200 : 500 );
});

var server = app.listen( 8080, function() {
    console.log( 'Server started!' );
});

module.exports = server;
