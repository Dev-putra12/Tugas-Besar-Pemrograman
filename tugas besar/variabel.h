//Header untuk menyimpan variable-variable yang digunakan pada program ini
#include <time.h>                                         // memanggil seluruh library yang mengandung waktu
#include "windows.h"                                       // memanggil seluruh library yang tersedia di windows.h
#include <string.h>																	        // memanggi seluruh library string.h



//Deklarasi variable global
int pilihanmenu; 																	          //variabel untuk pilihan menu pada program
int level;																			            // variabel untuk level permainan
int pilihanmasuk;
time_t waktuserver;                   											//variabel waktuserver   => berfungsi untuk mengambil waktu dari sistem.

char field[fieldSize][fieldSize]; 													// untuk menentukan baris
char field2[fieldSize][fieldSize]; 													// untuk menentukan kolom
unsigned int seed; 																	        // digunakan agar tidak ada angka yang bernilai negatif 
int x, y; 																			            // mendeklarasikan variabel x dan y
