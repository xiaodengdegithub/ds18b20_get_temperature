all:
	@echo "Add lib"
	make -C src
	@echo "Creat project"
	make -C project
run:
	@echo "Server running"
	make run -C project
clean:
	@echo "clean"
	make clean -C src

distclean: clean
	@echo "distclean"
	make uninstall -C src
	make distclean -C project

