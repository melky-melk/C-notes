all: msg_srv msg_cli msg_fun.h

run: msg_srv msg_cli
	./msg_srv

launch: msg_cli msg_srv
	./msg_cli

msg_srv: msg_srv.c msg_fun.h
	gcc msg_srv.c -o msg_srv -Wall -Wvla -Werror -std=gnu11 -Werror=format-security -O0 -fsanitize=address -g -lrt

msg_cli: msg_cli.c msg_fun.h
	gcc msg_cli.c -o msg_cli -Wall -Wvla -Werror -std=gnu11 -Werror=format-security -O0 -fsanitize=address -g -lrt

clean: msg_srv msg_cli
	rm msg_srv msg_c
