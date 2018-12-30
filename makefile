VPATH = include:src

OBJECTS = addressbook.o contact_databaseop.o contact.o
G++ = g++ -o $@ -c $<

addressbook.o: addressbook.cc addressbook.h contact_databaseop.h
	$(G++)

contact_databaseop.o: contact_databaseop.cc contact_databaseop.h
	$(G++)

contact.o: contact.cc contact.h
	$(G++)

clean:
	rm *.o
