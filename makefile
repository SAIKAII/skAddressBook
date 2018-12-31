VPATH = include:src

OBJECTS = main.o contact.o contact_databaseop.o addressbook.o
G++ = g++ -g -o $@ -c $<

simpleaddressbook: $(OBJECTS)
	g++ -o simpleaddressbook $(OBJECTS) `mysql_config --cflags --libs`

main.o: main.cc addressbook.h
	$(G++)

addressbook.o: addressbook.cc addressbook.h contact_databaseop.h
	$(G++)

contact_databaseop.o: contact_databaseop.cc contact_databaseop.h
	$(G++)

contact.o: contact.cc contact.h
	$(G++)

clean:
	rm *.o simpleaddressbook
