//Header yang berisi  fungsi-fungsi  yang digunakan pada Program Game Puzzle Number

#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include "structure.h"

//Deklarasi fungsi-fungsi yang digunkan pada Program Game Puzzle Number

void header ();										 				// Merupakan fungsi untuk menampilkan header yang berisi nama pembuat
void simbol();										 				// Merupakan fungsi untuk menampilkan simbol header
void error_alert();                                  				// Merupakan fungsi yang digunakan untuk menampilan pemberitahuan/pesan error
void menu_masuk();                                   				// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu masuk Login atau Register
void waktu();                                        				// Merupakan fungsi yang digunakan untuk menampilkan waktu pada sistem
void daftar();                                       				/* Fungsi void daftar() untuk menyimpan perintah-perintah yang dibutuhkan
                                                        			untuk registrasi yang akan menyimpan nama, username, serta password yang
                                                        			akan digunakan oleh pengguna*/

void masuk();                                        				/* Fungsi void masuk() digunakan untuk login/masuk dengan menggunakan akun yang telah dibuat
																	dan akan mengarahkan ke program utama*/
void menu();                                         				// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu game puzzle
void main_game();                                   				// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu level game puzzle  
void menu_petunjuk();                                				// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu petunjuk game puzzle 
void menu_tentang();                                 				// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu tentang game puzzle 
                                                        
void setcolor(unsigned short color){                              	//Fungsi setcolor untuk merubah warna teks
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);                                         
}

#endif
