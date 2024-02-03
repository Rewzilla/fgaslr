
CFLAGS		+= -I./ -DENABLE_GRAPH \
	-Wno-format-security -Wno-implicit-int -Wno-comment -Wno-unused-variable -Wno-return-type \
	-fno-stack-protector -g -D_FORTIFY_SOURCE=0 -DGAPING_SECURITY_HOLE

all:

	$(CC) $(CFLAGS) -c -o nc_jbuf.o nc_jbuf.c
	$(CC) $(CFLAGS) -c -o nc_jval.o nc_jval.c
	$(CC) $(CFLAGS) -c -o nc_netfd.o nc_netfd.c
	$(CC) $(CFLAGS) -c -o nc_ofd.o nc_ofd.c
	$(CC) $(CFLAGS) -c -o nc_unknown.o nc_unknown.c
	$(CC) $(CFLAGS) -c -o nc_p_tcp.o nc_p_tcp.c
	$(CC) $(CFLAGS) -c -o nc_p_udp.o nc_p_udp.c
	$(CC) $(CFLAGS) -c -o nc_h_errs.o nc_h_errs.c
	$(CC) $(CFLAGS) -c -o nc_gatesidx.o nc_gatesidx.c
	$(CC) $(CFLAGS) -c -o nc_gatesptr.o nc_gatesptr.c
	$(CC) $(CFLAGS) -c -o nc_Single.o nc_Single.c
	$(CC) $(CFLAGS) -c -o nc_insaved.o nc_insaved.c
	$(CC) $(CFLAGS) -c -o nc_wrote_out.o nc_wrote_out.c
	$(CC) $(CFLAGS) -c -o nc_wrote_net.o nc_wrote_net.c
	$(CC) $(CFLAGS) -c -o nc_wrote_txt.o nc_wrote_txt.c
	$(CC) $(CFLAGS) -c -o nc_hexnibs.o nc_hexnibs.c
	$(CC) $(CFLAGS) -c -o nc_timer1.o nc_timer1.c
	$(CC) $(CFLAGS) -c -o nc_timer2.o nc_timer2.c
	$(CC) $(CFLAGS) -c -o nc_lclend.o nc_lclend.c
	$(CC) $(CFLAGS) -c -o nc_remend.o nc_remend.c
	$(CC) $(CFLAGS) -c -o nc_gates.o nc_gates.c
	$(CC) $(CFLAGS) -c -o nc_optbuf.o nc_optbuf.c
	$(CC) $(CFLAGS) -c -o nc_bigbuf_in.o nc_bigbuf_in.c
	$(CC) $(CFLAGS) -c -o nc_bigbuf_net.o nc_bigbuf_net.c
	$(CC) $(CFLAGS) -c -o nc_ding1.o nc_ding1.c
	$(CC) $(CFLAGS) -c -o nc_ding2.o nc_ding2.c
	$(CC) $(CFLAGS) -c -o nc_portpoop.o nc_portpoop.c
	$(CC) $(CFLAGS) -c -o nc_stage.o nc_stage.c
	$(CC) $(CFLAGS) -c -o nc_o_alla.o nc_o_alla.c
	$(CC) $(CFLAGS) -c -o nc_o_interval.o nc_o_interval.c
	$(CC) $(CFLAGS) -c -o nc_o_listen.o nc_o_listen.c
	$(CC) $(CFLAGS) -c -o nc_o_nflag.o nc_o_nflag.c
	$(CC) $(CFLAGS) -c -o nc_o_wfile.o nc_o_wfile.c
	$(CC) $(CFLAGS) -c -o nc_o_random.o nc_o_random.c
	$(CC) $(CFLAGS) -c -o nc_o_udpmode.o nc_o_udpmode.c
	$(CC) $(CFLAGS) -c -o nc_o_verbose.o nc_o_verbose.c
	$(CC) $(CFLAGS) -c -o nc_o_wait.o nc_o_wait.c
	$(CC) $(CFLAGS) -c -o nc_o_zero.o nc_o_zero.c
	$(CC) $(CFLAGS) -c -o nc_o_tn.o nc_o_tn.c
	$(CC) $(CFLAGS) -c -o nc_holler.o nc_holler.c
	$(CC) $(CFLAGS) -c -o nc_bail.o nc_bail.c
	$(CC) $(CFLAGS) -c -o nc_catch.o nc_catch.c
	$(CC) $(CFLAGS) -c -o nc_tmtravel.o nc_tmtravel.c
	$(CC) $(CFLAGS) -c -o nc_arm.o nc_arm.c
	$(CC) $(CFLAGS) -c -o nc_Hmalloc.o nc_Hmalloc.c
	$(CC) $(CFLAGS) -c -o nc_findline.o nc_findline.c
	$(CC) $(CFLAGS) -c -o nc_comparehosts.o nc_comparehosts.c
	$(CC) $(CFLAGS) -c -o nc_gethostpoop.o nc_gethostpoop.c
	$(CC) $(CFLAGS) -c -o nc_getportpoop.o nc_getportpoop.c
	$(CC) $(CFLAGS) -c -o nc_nextport.o nc_nextport.c
	$(CC) $(CFLAGS) -c -o nc_loadports.o nc_loadports.c
	$(CC) $(CFLAGS) -c -o nc_pr00gie.o nc_pr00gie.c
	$(CC) $(CFLAGS) -c -o nc_doexec.o nc_doexec.c
	$(CC) $(CFLAGS) -c -o nc_doconnect.o nc_doconnect.c
	$(CC) $(CFLAGS) -c -o nc_dolisten.o nc_dolisten.c
	$(CC) $(CFLAGS) -c -o nc_udptest.o nc_udptest.c
	$(CC) $(CFLAGS) -c -o nc_oprint.o nc_oprint.c
	$(CC) $(CFLAGS) -c -o nc_atelnet.o nc_atelnet.c
	$(CC) $(CFLAGS) -c -o nc_readwrite.o nc_readwrite.c
	$(CC) $(CFLAGS) -c -o nc_main.o nc_main.c
	$(CC) $(CFLAGS) -c -o nc_helpme.o nc_helpme.c

	$(CC) $(CFLAGS) -g -o nc.bin nc.c \
		../src/fgaslr.c -D'PROG_NAME="nc"' \
		../src/cache.c ../src/mappings.c ../src/graph.c

clean:

	rm *.o *.bin
