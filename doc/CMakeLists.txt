FIND_PACKAGE(
	Doxygen
	REQUIRED)

SET(
	DOC_OUTPUT
	"${CMAKE_BINARY_DIR}/doc_generated")

CONFIGURE_FILE(
	Doxyfile.in
	"${DOC_OUTPUT}/Doxyfile")

# For now, use COPYONLY (since I don't know which escape sequences are in the
# html/css files that cmake might accidentally replace. Could be changed in
# the future.
CONFIGURE_FILE(
	header.html
	"${DOC_OUTPUT}/header.html"
	COPYONLY)

CONFIGURE_FILE(
	footer.html
	"${DOC_OUTPUT}/footer.html"
	COPYONLY)

CONFIGURE_FILE(
	stylesheet.css
	"${DOC_OUTPUT}/stylesheet.css"
	COPYONLY)

CONFIGURE_FILE(
	layout.xml
	"${DOC_OUTPUT}/layout.xml"
	COPYONLY)

ADD_CUSTOM_TARGET(
	doc)

ADD_CUSTOM_COMMAND(
	TARGET doc
	COMMAND ${DOXYGEN_EXECUTABLE}
	WORKING_DIRECTORY "${DOC_OUTPUT}")

fcppt_utils_install_doc_dir(
	INSTALL_DOC_DIR
)

INSTALL(
	DIRECTORY
	"${DOC_OUTPUT}/html"
	DESTINATION
	"${INSTALL_DOC_DIR}")
