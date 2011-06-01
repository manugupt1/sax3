file(MAKE_DIRECTORY /usr/share/sax3/res)
file(COPY . DESTINATION /usr/share/sax3/res PATTERN "*.png" PATTERN "*.txt" EXCLUDE)
