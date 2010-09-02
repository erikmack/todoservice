TESTS = \
	version.sh \
	invalid_uri.sh \
	invalid_method.sh

CLEANFILES = $(TESTS) \
	out.txt

COMMON_ECHO = \
	echo "export REQUEST_URI" >> $@ \
	&& echo "export REQUEST_METHOD" >> $@ \
	&& echo "../src/resttest >out.txt" >> $@
	
COMMON_POST_ECHO = \
	echo "rm -f out.txt" >> $@ \
	&& chmod +x $@


version.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep 200 out.txt >/dev/null || exit 1" >> $@
	echo "grep 0.3 out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

invalid_uri.sh:
	echo "REQUEST_URI=/dogs" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep 404 out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

invalid_method.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=PUT" >> $@
	$(COMMON_ECHO)
	echo "grep 405 out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

