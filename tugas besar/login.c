//Header yang di gunakan untuk standar input output pada bahasa C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Deklarasi variable global
int pilihanmasuk;
time_t waktuserver;                   //variavel waktuserver   => berfungsi untuk mengambil waktu dari sistem.

// Struct User untuk menyimpan member nama, username, password
typedef struct {
    char nama[50];
    char username[12];
    char password[10];
}User;

//Mendeklarasikan variabel u pada struct User
User u;

//Deklarasi fungsi-fungsi yang digunkan pada program game puzzle
void header ();
void error_alert();                                  /* Merupakan fungsi yang digunakan untuk menampilan pemberitahuan ketika user menginputkan
                                                        pilihan yang salah pada setiap switch case. */
void menu_masuk();                                   // Merupakan fungsi yang digunakan untuk menampilkan pilihan menu masuk Login atau Regristrasi
void waktu();                                        // Merupakan fungsi yang digunakan untuk menampilkan waktu pada sistem tempat user mengakses
void daftar();                                       /* Fungsi void daftar() untuk menyimpan perintah-perintah yang dibutuhkan
                                                        untuk registrasi yang akan menyimpan nama, username, serta password yang
                                                        akan digunakan oleh pengguna*/

void masuk();                                        /* Fungsi void masuk() digunakan agar pengguna dapat masuk dengan username serta
                                                        password yang sudah dibuat dan nantinya akan dilanjutkan kedalam fitur program*/
                                                        
// assign namaFile (nF) agar menyimpan string "RecordLogin.txt"
char namaFile[] = "RecordLogin.txt";

// fungsi main () adalah kepala dari program ini, dimana program akan di eksekusi oleh fungsi main ini.
int main (){
    header();
    system ("cls");
    menu_masuk();
}

//=======================================================================//
//**************  Fungsi Untuk Menampilkan Header/Judul  ****************//
//=======================================================================//
// Nama Fungsi    : header                                               //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi untuk menampilkan header/judul game dan       //
//                  pembuat                                              //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 09-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//

void header (){
    system ("cls");
	printf  ("\t\t\t\t\t====================================================\n");
	printf  ("\t\t\t\t\t||                   GAME PUZZLE                  ||\n");
	printf  ("\t\t\t\t\t====================================================\n");
	printf  ("\t\t\t\t\t||                Program dibuat oleh:            ||\n");
	printf  ("\t\t\t\t\t|| 1. IDA BAGUS MAS MANUABA    (2105551008)       ||\n");
	printf  ("\t\t\t\t\t|| 2. I PUTU AGUS PUTRA NEGARA (2105551044)       ||\n");
	printf  ("\t\t\t\t\t====================================================\n");
	printf  ("\t\t\t\t\t||       Tekan ENTER  untuk melanjutkan....       ||\n");
    printf  ("\t\t\t\t\t====================================================\n");
	getchar ();
    system ("cls");
}

//=======================================================================//
//***************  Fungsi Untuk Menampilkan Menu Masuk  *****************//
//=======================================================================//
// Nama Fungsi    : menu_masuk                                           //
// Input Argumen  : int pilihanmasuk                                     //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi untuk menampilkan menu awal game              //
//                  puzzle yaitu menu login, regristrasi dan exit        //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 09-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//
void menu_masuk(){
	mnmasuk:
	printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|          SELAMAT DATANG DI GAME PUZZLE         |\n");
    printf ("\t\t\t\t\t|  SILAHKAN LOGIN/REGRISTASI UNTUK DAPAT BERMAIN |\n");    
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|   No  |    MENU LOGIN/REGISTER                 |\n");
    printf ("\t\t\t\t\t|-------|----------------------------------------|\n");
    printf ("\t\t\t\t\t|   1   |    Login                               |\n");
    printf ("\t\t\t\t\t|   2   |    Registrasi                          |\n");   
    printf ("\t\t\t\t\t|   3   |    Exit                                |\n");
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|================================================|\n");
    printf ("\t\t\t\t\t|| Masukkan pilihan Anda : ");
    scanf  ("%d", &pilihanmasuk);
    printf ("\t\t\t\t\t|================================================|\n");
    // Membersihkan Layar terminal 
    system ("cls");
    
    /* Percabangan Switch dengan kondisi nilai yang disimpan pada variabel
       pilihan jika pengguna menuliskan 1 maka akan dipanggil fungsi masuk()
       jika pengguna menuliskna 2 maka akan dipanggil fungsi registrasi()    */
    switch (pilihanmasuk){
    case 1:
        // Jika pengguna menginput angka 1 maka dipanggil fungsi masuk
        masuk();
        break;
    case 2:
        // Jika pengguna menginput angka 2 maka dipanggil fungsi registrasi
        daftar();
        break;
    case 3:
    	// Jika pengguna menginput angka 3 maka akan keluar dari program
        exit(1);
        break;
    default:
        error_alert();
        // Kembali ke label mnmasuk jika terjadi kesalahan dalam menginput pilihan
        goto mnmasuk;
        break;
    }
}

//=======================================================================//
//********************* Fungsi Untuk  Daftar Akun ***********************//
//=======================================================================//
// Nama Fungsi    : void daftar()                           		     //
// Input Argumen  : char l.username[12], char l.password[10]             //
// Deskripsi      : Fungsi ini ditujukan untuk menginput username,       //
//                  serta password untuk disimpan pada file              //
//                  RecordLogin.txt yang nantinya akan divalidasi saat     //
//                  login                                    	         //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 09-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//
void daftar(){
    // Membuat pointer regis untuk file "RecordLogin.txt"
    FILE *regis;

    // Membuka file "RecordLogin.txt" dengan mode "w"
    regis = fopen(namaFile,"w");

    // Melakukan Pengecekan apakah pointer regis menunjuk kepada file yang dituju ("RecordLogin.txt")
    if (regis == NULL)
    {
        fputs("ERROR, File tidak ditemukan!", stderr);
        exit(1);
    }

    // Instruksi untuk menginput nama, username dan password
  printf("\t\t\t\t\t|===================================================|\n");
  printf("\t\t\t\t\t|                    MENU REGISTER                  |\n");
  printf("\t\t\t\t\t|---------------------------------------------------|\n");
  printf("\t\t\t\t\t|SILAHKAN LENGKAPI DATA DIBAWAH                     |\n");
  getchar();
  printf("\t\t\t\t\t|Masukkan Nama     : ");
  gets(u.nama);
  printf("\t\t\t\t\t|Masukkan Username : ");
  scanf("%s", u.username);
  printf("\t\t\t\t\t|Masukkan Password : ");
  scanf("%s", u.password);
  printf("\t\t\t\t\t|===================================================|\n");

    // Menuliskan nama yang diinput oleh pengguna kedalam file "RecordLogin.txt"
  fwrite(&u, sizeof(u), 1, regis);
  fclose(regis);
  printf("\t\t\t\t\t|===================================================|\n");
  printf("\t\t\t\t\t|                    BERHASIL REGISTER              |\n");
  printf("\t\t\t\t\t|---------------------------------------------------|\n");
  printf("\t\t\t\t\t|HALLO %s!                                   \n", u.nama);
  printf("\t\t\t\t\t|AKUN ANDA TELAH TERDAFTAR,SILAHKAN LOGIN DAN BERSENANG-SENANG ");
  printf("\t\t\t\t\t|===================================================|\n");
  getchar();
  printf("\t\t\t\t\t|             TEKAN ENTER UNTUK MELANJUTKAN         |\n");
    // Membersikan layar terminal
    system ("cls");
    // Memanggil fungsi masuk()
    masuk();
}

//=======================================================================//
//********* Fungsi Untuk Login dan Regis Akun serta Username ************//
//=======================================================================//
// Nama Fungsi    : void masuk()                            		     //
// Input Argumen  : char username[12], char password[10]                 //
// Output Argumen : l.username, l.password                               //
// Deskripsi      : Fungsi ini ditujukan untuk menginput username,       //
//                  serta password untuk berlanjut ke pada program       //
//                  Game Puzzle			                       	         //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 09-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//
void masuk(){
    /*  Variabel username[12] digunakan untuk menyimpan input username
        yang dilakukan oleh pengguna. Inputan tersebut akan divalidasi
        dengan username yang sudah terdaftar pada file RecordLogin.txt   */
    char username[12];

    /*  Variabel password[10] digunakan untuk menyimpan input password
        yang dilakukan oleh pengguna. Inputan tersebut akan divalidasi
        dengan password yang sudah terdaftar pada file RecordLogin.txt   */
    char password[10];

    // Variabel pilihan untuk pilihan user apakah ingin mendaftar atau keluar
    int pilihan;

    // Membuat pointer record untuk menunjuk pada file "RecordLogin.txt"
    FILE *record;
    // Membuka file dengan mode "r"
    record = fopen (namaFile, "r");
    if (record == NULL){
        fputs ("Error, Tidak terdapat File untuk penyimpanan akun\n", stderr);
        daftar();
    }

    // Memperlihatkan tanggal login
    waktu();
    // Instruksi untuk LOGIN
  printf("\t\t\t\t\t|===================================================|\n");
  printf("\t\t\t\t\t|                    MENU LOGIN                     |\n");
  printf("\t\t\t\t\t|---------------------------------------------------|\n");
  printf("\t\t\t\t\t|SILAHKAN LOGIN DENGAN AKUN ANDA                    |\n");
  printf("\t\t\t\t\t|Masukkan Username : ");
  scanf("%s", username);
  printf("\t\t\t\t\t|Masukkan Password : ");
  scanf("%s", password);
  printf("\t\t\t\t\t|===================================================|\n");
  system("cls");
    // Membeaca file "RecordLogin.txt"
    while(fread(&u,sizeof(u),1,record)){
        /*  Mengkomparasi username serta password yang diinput pengguna kedalam fungsi
            masuk() dengan username serta password yang sudah terdaftar */
        if(strcmp(username, u.username)==0 && strcmp(password, u.password)==0){
            printf("\t\t\t\t\t|================================================|\n");
      		printf("\t\t\t\t\t|                   LOGIN BERHASIL               |\n");
      		printf("\t\t\t\t\t|================================================|\n");
        }
        //  Jika akun tidak terdaftar maka akan diberikan pilihan untuk mendaftar atau keluar dari program
        else {
            printf("\t\t\t\t\t|================================================|\n");
      		printf("\t\t\t\t\t|               AKUN TIDAK TERDAFTAR             |\n");
      		printf("\t\t\t\t\t|================================================|\n");

            mnmasuk:
            printf("\t\t\t\t\t|===================================================|\n");
      		printf("\t\t\t\t\t|  NO  |    MENU LOGIN/REGISTER                     |\n");
      		printf("\t\t\t\t\t|------|--------------------------------------------|\n");
      		printf("\t\t\t\t\t|  1   |    LOGIN ULANG                             |\n");
      		printf("\t\t\t\t\t|  2   |    REGISTER                                |\n");
      		printf("\t\t\t\t\t|  3   |    EXIT                                    |\n");
      		printf("\t\t\t\t\t|===================================================|\n");
      		printf("\t\t\t\t\t|===================================================|\n");
      		printf("\t\t\t\t\t|| MASUKAN PILIHAN ANDA : ");
      		scanf("%d", &pilihan);
      		system("cls");
            // Jika pengguna mengetik nomor 1 maka akan dialihkan kepada fungsi daftar
            if (pilihan == 1){
                masuk();
            /* Menggunakan fungsi recursive kepada fungsi masuk agar pengguna
               dapat melakukan percobaan masuk kembali jika terjadi kesalahan penulisan */
            } else if (pilihan==2) {
                daftar();
            } else if (pilihan ==3){
                exit(1);
            } else {
                printf("\t\t\t\t\t|================================================|\n");
        		printf("\t\t\t\t\t|               PILIHAN TIDAK TERSEDIA           |\n");
        		printf("\t\t\t\t\t|================================================|\n");
                goto mnmasuk;
            }
        }
    }
    fclose(record);
    return;
}

//=======================================================================//
//**************   Fungsi Untuk Menampilkan Pesan Eror   ****************//
//=======================================================================//
// Nama Fungsi    : -                                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menampilkan Pemberitahuan Bahwa user memasukan input //
//                  bahwa user salah memasukkan pilihan.                 //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 09-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//
void error_alert(){
    printf("\t\t\t\t\t|================================================|\n");
  	printf("\t\t\t\t\t|               PILIHAN TIDAK TERSEDIA           |\n");
  	printf("\t\t\t\t\t|     SILAHKAN MEMILIH PILIHAN YANG SUDAH ADA    |\n");
  	printf("\t\t\t\t\t|================================================|\n");
}

//=======================================================================//
//***********     Fungsi Untuk Menampilkan Waktu Sistem     *************//
//=======================================================================//
// Nama Fungsi    : waktu                                                //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi ini digunakan untuk mengambil dan menampilkan //
//                 Waktu sistem pada saat user mengakses program.        //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 09-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//
void waktu(){
    time( & waktuserver);
    struct tm * waktu = localtime( & waktuserver);
    printf("\n\t\t\t\t\t||================Tanggal: %i/%i/%i==============||\n\n", waktu -> tm_mday, waktu -> tm_mon + 1, waktu -> tm_year + 1900);
}
