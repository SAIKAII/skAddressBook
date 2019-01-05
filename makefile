VPATH = include:src:util

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

message_packet_and_unpacking.o: message_packet_and_unpacking.cc message_packet_and_unpacking.h message.h base64_tool.h
	$(G++)

onlinedbop.o: onlinedbop.cc onlinedbop.h global_config.h
	$(G++)

global_config.o: global_config.cc global_config.h contact_databaseop.h contact.h
	$(G++)

communicationclient.o: communicationclient.cc communicationclient.h epollop.h event_timer.h
	$(G++)

event_timer.o: event_timer.cc event_timer.h epollop.h
	$(G++)

clean:
	rm *.o simpleaddressbook
