U3D parser tool makes a text dump of U3D binary file in XML format,
The following command parses filename.u3d file and generates XML
dump in stdout:
        > u3dparsefilei32.exe filename.u3d

U3D parser reads blocks according to Universal 3D File Format standard
(ECMA-363 3rd Edition / June 2006) and obtains name of each
block and all information about the following blocks only:

-       0x00443355 - File Header
-       0xFFFFFF12 - File Reference
-       0xFFFFFF14 - Modifier Chain
-       0xFFFFFF15 - Priority Update
-       0xFFFFFF16 - New Object Type

-       0xFFFFFF21 - Group Node
-       0xFFFFFF22 - Model Node
-       0xFFFFFF23 - Light Node
-       0xFFFFFF24 - View Node

-       0xFFFFFF41 - 2D Glyph Modifier

-       0xFFFFFF51 - Light Resource
-       0xFFFFFF52 - View Resource
-       0xFFFFFF53 - Lit Texture Shader


The structure of generated XML file should be valid against u3d.dtd
that is located in binary folder.

U3D parses depends on LibXML libraries, in order to build U3D parser you 
should put 
 - the following h-files to folder dependencies\include
	iconv.h
	libxml
	zconf.h
	zlib.h
	libxml/c14n.h
	libxml/catalog.h
	libxml/chvalid.h
	libxml/debugXML.h
	libxml/dict.h
	libxml/DOCBparser.h
	libxml/encoding.h
	libxml/entities.h
	libxml/globals.h
	libxml/hash.h
	libxml/HTMLparser.h
	libxml/HTMLtree.h
	libxml/list.h
	libxml/nanoftp.h
	libxml/nanohttp.h
	libxml/parser.h
	libxml/parserInternals.h
	libxml/pattern.h
	libxml/relaxng.h
	libxml/SAX.h
	libxml/SAX2.h
	libxml/schemasInternals.h
	libxml/schematron.h
	libxml/threads.h
	libxml/tree.h
	libxml/uri.h
	libxml/valid.h
	libxml/xinclude.h
	libxml/xlink.h
	libxml/xmlautomata.h
	libxml/xmlerror.h
	libxml/xmlexports.h
	libxml/xmlIO.h
	libxml/xmlmemory.h
	libxml/xmlmodule.h
	libxml/xmlreader.h
	libxml/xmlregexp.h
	libxml/xmlsave.h
	libxml/xmlschemas.h
	libxml/xmlschemastypes.h
	libxml/xmlstring.h
	libxml/xmlunicode.h
	libxml/xmlversion.h
	libxml/xmlwin32version.h
	libxml/xmlwriter.h
	libxml/xpath.h
	libxml/xpathInternals.h
	libxml/xpointer.h
- the following libXML libraries to folder dependencies\lib
	libeay32
	libssleay32
	libwsock32
	libxml2

LibXML tools can be founded by the following link http://www.xmlsoft.org/
