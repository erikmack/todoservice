TESTS = \
	test_case_050.sh \
	test_case_060.sh \
	test_case_900.sh

CLEANFILES = $(TESTS) \
	out.txt

COMMON_ECHO = \
	echo "export REQUEST_URI" >> $@ \
	&& echo "export REQUEST_METHOD" >> $@ \
	&& echo "../src/todoservice >out.txt" >> $@
	
COMMON_POST_ECHO = \
	echo "rm -f out.txt" >> $@ \
	&& chmod +x $@


test_case_050.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"HTTP/1.1 200 OK\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"major=\\\"1\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"minor=\\\"0\\\"\" out.txt >/dev/null || exit 1" >> $@
	echo "grep \"age=\\\"0\\\"\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_060.sh:
	echo "REQUEST_URI=/version" > $@
	echo "REQUEST_METHOD=PUT" >> $@
	$(COMMON_ECHO)
	echo "grep \"HTTP/1.1 405 Method not allowed\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

test_case_900.sh:
	echo "REQUEST_URI=/dogs" > $@
	echo "REQUEST_METHOD=GET" >> $@
	$(COMMON_ECHO)
	echo "grep \"HTTP/1.1 404 File not found\" out.txt >/dev/null || exit 1" >> $@
	$(COMMON_POST_ECHO)

