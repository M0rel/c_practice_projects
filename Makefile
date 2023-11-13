all:
	$(MAKE) -C template/
	$(MAKE) -C sockets/

clean:
	$(MAKE) clean -C template/
	$(MAKE) clean -C sockets/

