#ifndef __TEST_H__
#define __TEST_H__

extern void test_share_mem_write();
extern void test_share_mem_read();
extern int test_unix_tcp_server();
extern int test_unix_tcp_client_send();
extern int test_unix_udp_client_send();
extern int test_unix_udp_client_recieve();
extern void test_state_machine();
extern void test_map();
extern void test_datastructure_hashlist();
extern int test_datastructure_link_list();
extern int test_datastructure_rbtree_map(void);
extern int test_datastructure_vector();
extern void test_datastructure_ring_buffer();
extern int test_inet_server();
extern int test_inet_tcp_client_send();
extern int test_inet_udp_client_recieve();
extern int test_inet_udp_client_send();
extern int test_inet_udp_client_broadcast();
extern void test_ctr_alloc();
extern int test_tmr_user();
extern void test_io_user();
extern int test_io();
extern int test_signal();
extern int test_time();
extern int test_pdt_proto_analyzer();
extern void test_client_recv_of_inet_udp();
extern void test_client_recv_of_unix_udp();
extern int test_server_of_unix();
extern int test_server_of_inet();
extern void test_pa_admin();
extern void test_blob();
extern void test_bus_daemon();
extern void test_bus_client();
extern void test_bus_server();
extern void bus_debug_service();
extern void bus_debug_client(char *bussiness, char *sw, char *level);
extern int test_array_stack();
extern int test_miscellany_net();
extern int lab();
extern int lab2();
extern int lab3();
extern void lab5();
extern int lab6(int argc,char **argv);
extern void args_print_help_test_info(args_processor_t *p);
extern int test_json(void);
extern int test_inet_wireless(int argc, char **argv);
extern int test_configurator(void);  
extern void test_obj();
extern void test_ui_container();
extern void test_ui_button();
extern void test_obj_iter();
extern void test_obj_hiter();
extern int test_sdl( int argc, char* args[]);
extern void test_obj_sdl_character();
extern void test_ui_painter();
extern void test_obj_subject();
extern void test_obj_enemy();
extern void test_obj_string();
extern void test_obj_map();
extern void test_obj_hash_map();
extern void test_obj_vector();
extern void test_obj_llist_list();
extern void test_ui_graph();
extern void test_ui_window();
extern void test_obj_text();
extern void test_ui_text_area();
extern void test_ui_text_field();
extern void test_obj_image();
extern void test_obj_sdl_text();
extern void test_obj_sdl_image();
extern void test_obj_sdl_event();
extern void test_obj_sdl_font();
extern void test_obj_sdl_timer();
extern void test_ui_sdl_window();
extern void test_ui_grid_layout();
extern void test_ui_border_layout();
extern void test_ui_label();
extern void test_ui_box();
extern void test_ui_button();
extern int test_object_config();
extern void test_obj_select_base();
extern int test_event_io();
extern void test_obj_udp_socket();
extern void test_obj_thread();
extern void test_udp_socket_recv();
extern void test_udp_socket_send();
extern void test_tcp_socket_recv();
extern void test_tcp_socket_send();
extern void test_unix_udp_socket_send();
extern void test_unix_udp_socket_recv();
extern void test_obj_mutex_lock();
extern int test_obj_array_stack();
extern void test_obj_linked_queue();
extern int test_heap();
extern void test_obj_event_thread();
extern void test_obj_worker();
extern void test_obj_io_worker();
extern void test_obj_timer_worker();
extern void test_obj_server();
extern void test_obj_client();

#endif
