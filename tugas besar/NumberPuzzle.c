// Deklarasi file header 
#include <stdlib.h> 																// memanggil seluruh library standar bahasa c
#include <time.h> 																	// memanggil seluruh library yang mengandung waktu
#include <stdio.h> 																	// memanggil seluruh library input output
#include <windows.h>																// memanggil seluruh library yang tersedia di windows.h
#include <string.h>																	// memanggi seluruh library string.h

#define atas 1 																		//membuat urutan atas menjadi nomor 1
#define kiri 2 																		//membuat urutan kiri menjadi nomor 2
#define bawah 3 																	//membuat urutan bawah menjadi nomor 3
#define kanan 4 																	//membuat urutan kanan menjadi nomor 4

#define keyUp 0x048																	// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah atas 
#define keyDown 0x050 																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah bawah 
#define keyLeft 0x04b 																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah kiri 
#define keyRight 0x04d																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah kanan 

#define true 1 																		// mendefinisikan bahwa boolean 1 adalah true 
#define false 0 																	// mendefinisikan bahwa boolean 0 adalah false

#define easy 2 																		// untuk membuat game puzzle memiliki 10 kolom
#define medium 10 																	// untuk membuat game puzzle memiliki 20 kolom
#define hard 20 																	// untuk membuat game puzzle memiliki 30 kolom

#define fieldSize 4 																// untuk membuat dimensi game puzzle menjadi 4

//Deklarasi variable global
int pilihanmenu; 																	//variabel untuk pilihan menu pada program																		// variabel untuk level permainan
int pilihanmasuk;
int moves = -1;
char score = 0;
char level = 1;
time_t waktuserver;                   												//variabel waktuserver   => berfungsi untuk mengambil waktu dari sistem.

char field[fieldSize][fieldSize]; 													// untuk menentukan baris
char field2[fieldSize][fieldSize]; 													// untuk menentukan kolom
unsigned int seed; 																	// digunakan agar tidak ada angka yang bernilai negatif 
int x, y; 																			// mendeklarasikan variabel x dan y
 
// assign namaFile (nF) agar menyimpan string "RecordLogin.txt"
char namaFile[] = "RecordLogin.txt";

// Struct User untuk menyimpan member nama, username, password
typedef struct {
    char nama[50];
    char username[12];
    char password[10];
}User;

//Mendeklarasikan variabel u pada struct User
User u;

//Deklarasi fungsi-fungsi yang digunkan pada program game puzzle
void simbol();
void header ();										 							// Merupakan fungsi untuk menampilkan header yang berisi nama pembuat
void error_alert();                                  							/* Merupakan fungsi yang digunakan untuk menampilan pemberitahuan ketika user menginputkan
                                                        							pilihan yang salah pada setiap switch case. */
void menu_masuk();                                   							// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu masuk Login atau Regristrasi                                                        
void menu();                                         							// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu game puzzle
void main_game();                                    							// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu level game puzzle  
void menu_petunjuk();                               	 						// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu level game puzzle 
void menu_tentang();                                 							// Merupakan fungsi yang digunakan untuk menampilkan pilihan menu level game puzzle 
void waktu();                                        							// Merupakan fungsi yang digunakan untuk menampilkan waktu pada sistem tempat user mengakses
void daftar();                                       							/* Fungsi void daftar() untuk menyimpan perintah-perintah yang dibutuhkan
                                                       							   untuk registrasi yang akan menyimpan nama, username, serta password yang
                                                        						   akan digunakan oleh pengguna*/

void masuk();                                        							/* Fungsi void masuk() digunakan agar pengguna dapat masuk dengan username serta
                                                        						   password yang sudah dibuat dan nantinya akan dilanjutkan kedalam fitur program*/
int acak(int i); 																// untuk membuat nilai acak pada kolom puzzle
void initField(int movement); 													// untuk membuat pergerakan di dalam game puzzle 
void move(int arah);															// untuk menentukan arah gerak pada game puzzle
void generateOutput();															// untuk membuat tampilan output pada game puzzle
int cekUrut();																	// untuk melakukan pengecekan apakah nilai sudah urut agar puzzle bisa tau benar atau salah

void setcolor(unsigned short color){                                           //pembuatan fungsi set color untuk merubah warna teks
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);           //pembuatan fungsi set color untuk merubah warna teks
}


// fungsi main () adalah kepala dari program ini, dimana program akan di eksekusi oleh fungsi main ini.
int main ()
{
    header(); 																	//memanggil fungsi header
    system ("cls"); 															// fungsi untuk membersihkan layar
    menu_masuk();																//memanggil fungsi menu_masuk

}
// fungsi ini adalah untuk melakukan pengacakan kepada nilai nilai dari puzzle agar permainan puzzle angka menjadi lebih menarik 
int acak(int i) 
{
    int a; 																		// variabel a yang memiliki tipe data integer
    seed += 5; 																	//nilai seed ditambah 5
    srand(seed); 																//melakukan pengacakan random dari nilai seed 

    a = (rand() % i) + 1;														//variabel a menyimpan nilai angka random yang dimoduluskan dengan i dan ditambah 1

    return(a);																	//nilai dikembalikan ke variabel a
}

//fungsi initfield dengan parameter movement bertipe data integer
void initField(int movement) 
{
    int arah, arahOld = -1, nPindah = movement, xOld, yOld; 							//deklarasi variabel bertipe data integer
    int c = 1, i, j;																	//deklarasi variabel bertipe data integer	
    char temp;																			//variabel temp bertipe data character

    srand(time(NULL));																	//untuk memunculkan angka random yang polanya tidak sama seperti yang telah ditampilkan sebelumnya
    seed = rand();																		//angka random akan disimpan di variabel seed
    x = y = (fieldSize - 1);															//nilai x disamadengankan nilai y disamadengankan fieldsize-1 

    for (i = 0; i <= (fieldSize - 1); i++) {											//perulangan for
        for (j = 0; j <= (fieldSize - 1); j++) {										//perulangan for
            field[i][j] = field2[i][j] = c;												//array field [i][j] sama dengan field2[i][j] sama dengan c
            c++;																		//nilai c ditambah 1
        }
    }
    field[fieldSize - 1][fieldSize - 1] = field2[fieldSize - 1][fieldSize - 1] = ' ';	//array field [fieldsize-1][fieldsize-1] = field2[fieldSize - 1][fieldSize - 1]

    c = 0;																				//nilai c=0
    while (c != nPindah) 																//perulangan while apabila nilai c tidak sama dengan nilai variabel npindah
	{
        xOld = x;																		//nilai xOld = x
        yOld = y;																		//nilai yOld = y
        arah = acak(4);																	//variabel arah menyimpan nilai fungsi acak dengan parameter nilai 4

        if (arah != 0) {																//jika nilai variabel arah tidak sama denga 0 
            if ( c != 0) {																//jika nilai variabel c tidak sama dengan 0
                if ((arah + 2) % 4 == arahOld) {										//jika nilai arah ditambah 2 dan dimoduluskan 4 sama dengan arahOld
                    continue;															//melewatkan semua perintah dibawahnya dan langsung melompat ke bagian kondisi perulangan
                }
            }

            switch (arah) {																//percabangan switch case dengan variabel arah 
                case atas :																//jika arah=atas
                    if (y > 0) y--;
                    else continue;
                    break;																//keluar dari percabangan switch case
                case kiri:																//jika arah=kiri
                    if (x > 0) x--;
                    else continue;
                    break;																//keluar dari percabangan switch case
                case kanan :															//jika arah=kanan
                    if (x < fieldSize - 1) x++;
                    else continue;
                    break;																//keluar dari percabangan switch case
                case bawah :															//jika arah=bawah
                    if (y < fieldSize - 1) y++;
                    else continue;
                    break;																//keluar dari percabangan switch case
                default :																//jika tidak
                    break;																//keluar dari percabangan switch case
            }

            if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {		//jika nilai x >= 0 dan y >= 0 dan x <= fieldSize - 1 dan y <= fieldSize - 1
                temp = field[y][x];														//variabel temp disamadengankan array field [y][x]
                field[y][x] = field[yOld][xOld];										//array field [y][x] disamadengankan array field [yOld][xOld]
                field[yOld][xOld] = temp;												//array field[yOld][xOld] disamadengankan temp

                c++;																	//nilai c ditambah 1
                arahOld = arah % 4;														//variabel arahOld menyimpan nilai arah yang dimoduluskan dengan 4
            } else {																	//jika tidak
                x = xOld;																//nilai x disamadengankan nilai xOld
                y = yOld;																//nilai y disamadengankan nilai yOld
            }
        }
    }
}


//fungsi move dengan bertipe data integer dengan parameter bertipe data integer
void move(int arah) 																	
{
    int xOld, yOld;																		//variabel xOld dan Yold bertipe data integer
    char temp;																			//variabel temp bertipe data char

    xOld = x;																			//nilai xOld = x
    yOld = y;																			//nilai yOld = y

    switch (arah) {																		//switch case arah
        case atas :																		//jika arah = atas
            if (y > 0) y--;																//jika nilai y > 0, nilai y dikurangi 1 
            break;																		//keluar dari swtich case
        case kiri:																		//jika arah = kiri 
            if (x > 0) x--;																//jika nilai x > 0, nilai x dikurangi 1
            break;																		//keluar dari switch case
        case kanan :																	//jika arah = kanan
            if (x < (fieldSize - 1)) x++;												//jika nilai x < fieldsize-1, nilai x ditambah 1 
            break;																		//keluar dari switch case 
        case bawah :																	//jika arah = bawah 
            if (y < (fieldSize - 1)) y++;												//jika nilai y < fieldsize-1, nilai y ditambah 1
            break;																		//keluar dariu switch case
        default :																		//jika tidak
            break;																		//keluar dari switch case
    }

    if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {				//jika nilai x >=0 dan y>=0 dan x <= fieldsize-1 dan y<=fieldsize-1 
        temp = field[y][x];																//variabel temp disamadengankan field[y][x]
        field[y][x] = field[yOld][xOld];												//array field[y][x] disamadengankan array field[yOld][xOld]
        field[yOld][xOld] = temp;														//array field[yOld][xOld] disamadengankan temp
    } else {																			//jika tidak
        x = xOld;																		//nilai x disamadengankan xOld
        y = yOld;																		//nilai y disamadengankan yOld
    }
    generateOutput();																	//memanggil fungsi generateOutput
}


//fungsi generateOutput yang menampilkan tampilan saat user sudah login
void generateOutput() 
{
    int i, j, k;																						//membuat variabel dengan tipe data integer
    system ("cls");																						//untuk membersihkan layar
	simbol();																							//untuk memanggil fungsi simbol
	setcolor(14);																						//untuk menggunakan warna dengan kode warna 14
	printf("\n\t\t                         A Y O  S E L E S A I K A N                       ");         //untuk menampilkan tulisan didalam tanda petik             
    printf("\n\t\t                      G A M E  P U Z Z L E  N U M B E R         \n");					//untuk menampilkan tulisan didalam tanda petik  
    printf("\n\t\t                               L E V E L  %d                     \n", level);			//untuk menampilkan tulisan didalam tanda petik  
    printf("\n\t\t     ----------------------------------------------------------------    ");			//untuk menampilkan tulisan didalam tanda petik  
	printf("\n\t\t        ==============================================================\n");			//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t        ||  Mainkan Puzzle dan Susunlah Menjadi Urutan Yang Benar!  ||\n");				//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t        ||   Geser Kotak Kosong Hingga Menjadi Angka Yang Berurut   ||\n");				//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t        ==============================================================\n\n");			//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t\t\t\t   ");																			//untuk menampilkan tulisan didalam tanda petik  
    for(k = 1; k <= fieldSize; k++) 																	//perulangan for
	printf("+----"); 																					//menampilkan teks dalam tanda kutip
	puts("+");																							//menampilkan teks dalam tanda kutip disertai perpindahan

    for (i = 0; i<=(fieldSize - 1); i++) {																//perulangan for
    	printf("\t\t\t\t\t   ");																		//menampilkan teks dalam tanda kutip
        for (j= 0; j<=(fieldSize - 1); j++) {															//perulangan for	
            if (i == y && j == x) {																		//jika i = y dan j = x
                printf("| %c  ", field[i][j]);															//untuk menampilkan teks bertipe data char dari array field[i][j]
            } else {																					//jika tidak
                printf("| %2i ", field[i][j]);															//untuk menampilkan teks bertipe data integer dari array field[i][j]
            }
        }
        puts("|");																						//menampilkan teks dalam tanda kutip disertai dengan perpindahan baris
		printf("\t\t\t\t\t   ");																		//menampilkan teks dalam tanda kutip
        for(k = 1; k <= fieldSize; k++) 																//perulangan for
		printf("+----"); 																				//menampilkan teks dalam tanda kutip
		puts("+");																						//menampilkan teks dalam kutip dengan perpindahan baris
    }
    		moves++;
            printf("\n  MOVES: %d\tSCORE: %d\tLEVEL: %d\n", moves, score, level);
	puts    ("\n\t\t   || -------- Tekan ESC untuk Keluar / Reset Permainan . . . -------- ||\n");		//menampilkan teks dalam kutip dengan perpindahan baris
}



//fungsi untuk melakukan pengecekan pada nilai puzzle 
int cekUrut() 																							
{
    int c, d;																							//variabel bertipe data integer
    int match = true;																					//variabel match = true bertipe data integer

    for (c = 0; c <= (fieldSize - 1); c++) {															//perulangan for
        for (d = 0; d <= (fieldSize - 1); d++) {														//perulangan for
            if (field[c][d] != field2[c][d]) {															//jika array field[c][d] tidak sama dengan array field2[c][d]
                if (match == true) {																	//jika match = true
                    match = false;																		//jika match = false
                }
            }
        }
    }
    return(match);																						//mengembalikan nilai ke variabel match
}

//=======================================================================//
//**************   Fungsi Untuk Menampilkan Menu Level  *****************//
//=======================================================================//
// Nama Fungsi    : -                                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menampilkan menu pilihan level yang ada pada game ini//
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 20-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//

//=======================================================================//
//************    Menambahkan beberapa tampilan di level  ***************//
//=======================================================================//
// Nama Fungsi    : -                                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menambahkan beberapa desain dan alert di menu level  //
//                                                                       //
// Versi : 1.1                                      Rev. 0               //
// Tgl   : 22-12-2021                               Tgl: -               //
// I putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//

//=======================================================================//
//**************   Memperbaiki Error Pada Level Puzzle  *****************//
//=======================================================================//
// Nama Fungsi    : -                                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Memperbaiki error pada bagian level game puzzle   	 //
//                                                                       //
// Versi : 1.2                                      Rev. 0               //
// Tgl   : 22-12-2021                               Tgl: -               //
// I putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//


//fungsi ini unutk memilih level kesulitan pada game puzzle 
void main_game() 
{
	int i, j, k;																						//variabel bertipe data integer
    char key;																							//variabel key bertipe data char
    for(;;) {																							//menggunakan for
    simbol();																							//memanggil fungsi simbol
	setcolor(14);																						//setting agar menggunakan warna dengan kode 14
	printf("\n\t\t    S E L A M A T   D A T A N G  D I  G A M E  P U Z Z L E  N U M B E R");            //untuk menampilkan teks didalam tanda petik          
    printf("\n\t\t                 S I L A H K A N  P I L I H  L E V E L\n");							//untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t     ----------------------------------------------------------------    ");			//untuk menampilkan teks didalam tanda petik 
    setcolor(6);																						//untuk setting agar menggunakan warna dengan kode 6
    printf("\n\n\t\t                          P I L I H  L E V E L                       \n");          //untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t                       |  1. EASY              |             ");                      //untuk menampilkan teks didalam tanda petik      
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik          
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       |  2. MEDIUM            |             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       |  3. HARD              |             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       |  4. KEMBALI           |             ");                      //untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");						//untuk menampilkan teks didalam tanda petik 
    printf("\n\n\t\t        ===================================================\n");					//untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t                      Masukkan pilihan Anda : ");										//untuk menampilkan teks didalam tanda petik 
    scanf ("%d", &level);																				//untuk penggunakan memasukan level yang dipilih
    system("cls");																						//membersihkan layar


        switch (level) {																				//switch case
            case 1 :																					//jika case 1 adalah easy
                initField(easy);																		//memanggil field easy
                break;																					//keluar dari switch case
            case 2 :																					//jika case 2 adalah medium
                initField(medium);																		//memanggil field medium
                break;																					//keluar dari switch case
            case 3 :																					//jika case 3 adalah hard
                initField(hard);																		//memanggil field hard
                break;																					//keluar dari switch case
            case 4 :																					//jika case 4 adalah menu
                menu();																					//memanggil function menu
                break;																					//keluar dari switch case
            default :																					//jika tidak
                puts("\n\t\t                       ------------------------------             ");       //menampilkan teks dalam kutip dengan perpindahan baris                  
    			puts("\n\t\t             	       |LEVEL YANG ANDA PILIH SALAH |             ");		//menampilkan teks dalam kutip dengan perpindahan baris
				puts("\n\t\t             	       |MASUKKAN LEVEL YANG TERSEDIA|             ");       //menampilkan teks dalam kutip dengan perpindahan baris
    			puts("\n\t\t                       ------------------------------             ");		//menampilkan teks dalam kutip dengan perpindahan baris
                getch();																				//menahan tampilan pada layar
                continue;																				//melewatkan semua perintah dibawahnya dan langsung melompat ke bagian kondisi perulangan
        }
        
        system("cls");																					//membersihkan layar

        generateOutput();																				//memanggil fungsi generateOutput

        while ((key = getch()) != 27) {																	//kondisi while
            switch(key) {																				//switch key 
                case keyUp :																			//jika switch key atas
                    move(atas);																			//move ke atas
                    break;																				//keluar dari case
                case keyDown :																			//jika keyDown
                    move(bawah);																		//move kebawah
                    break;																				//keluar dari case
                case keyLeft :																			//jika keyLeft
                    move(kiri);																			//move ke kiri
                    break;																				//keluar dari case
                case keyRight :																			//jika keyRight
                    move(kanan);																		//move ke kanan
                    break;																				//keluar dari case
            }
            if (cekUrut() == true) {																	//jika cekUrut = true
                puts("\n\t\t                       -------------------------             ");            //menampilkan teks dalam kutip dengan perpindahan baris             
    			puts("\n\t\t             	       |SELAMAT, ANDA MENANG!!!|             ");            //menampilkan teks dalam kutip dengan perpindahan baris               
    			puts("\n\t\t                       -------------------------             "); 			//menampilkan teks dalam kutip dengan perpindahan baris
    			score++;
    			moves = -1;
                break;																					//keluar dari while 
            }
        }
        if (key == 'q') {																				//jika key q ditekan
            printf("Apakah anda ingin keluar ?\n['y' utk keluar / 't' utk reset] : \n");				//untuk menampilkan teks didalam tanda petik
            if (toupper(getchar()) == 'Y') break;														
            else continue;
        } else {
        	printf("\n\t\t   	|| -------- Silahkan Pilih Level Untuk Tetap Bermain -------- ||\n");	//untuk menampilkan teks didalam tanda petik
            if (toupper(getchar()) == 'T') {
                puts("\nTerima Kasih Telah Mencoba!!!");												//untuk menampilkan teks didalam tanda petik dengan perpindahan baris
                getch();																				//untuk menahan tampilan 
                break;																					//untuk kelaur dari kondisi if else
            }
            else continue;
        }
    }
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
// Tgl   : 19-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//

//fungsi header
void header () 
{
	setcolor(6); 																					// membuat warna tulisan dengan kode warna 6
	simbol(); 																						//fungsi simbol
    printf("\n\t\t                      G A M E  P U Z Z L E  N U M B E R         \n");				//menampilkan teks dalam tanda kutip 
    printf("\n\t\t     ----------------------------------------------------------------    ");		//menampilkan teks dalam tanda kutip 
    printf  ("\n\t\t        ===========================================================\n");		//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||         P R O G R A M  D I B U A T  O L E H :       ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||                                                     ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||    1. IDA BAGUS MAS MANUABA (2105551008)            ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||                                                     ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||    2. I PUTU AGUS PUTRA NEGARA (2105551044)         ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||                                                     ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         =========================================================\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||                                                     ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||         Tekan ENTER  untuk Melanjutkan . . .        ||\n");			//menampilkan teks dalam tanda kutip 
	printf  ("\t\t         ||                                                     ||\n");			//menampilkan teks dalam tanda kutip 
    printf  ("\t\t         =========================================================\n");			//menampilkan teks dalam tanda kutip 
	getchar ();																						//untuk menahan tampilan
    system ("cls");																					//untuk membersihkan layar
   
}

//=======================================================================//
//***************  Fungsi Untuk Menampilkan Menu Utama  *****************//
//=======================================================================//
// Nama Fungsi    : menu                                                 //
// Input Argumen  : int pilihanmenu                                      //
// Output Argumen : -                                                    //
// Deskripsi      : Fungsi untuk menampilkan menu utama game             //
//                  puzzle yaitu menu main, petunjuk, tentang dan exit   //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 19-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//

//fungsi dari menu
void menu()
{
	menu:																							//membuat 
	simbol();
	setcolor(14);
	printf("\n\t\t    S E L A M A T   D A T A N G  D I  G A M E  P U Z Z L E  N U M B E R");                      
    printf("\n\t\t           S I L A H K A N  P I L I H  M E N U  D I B A W A H\n");
    printf("\n\t\t     ----------------------------------------------------------------    ");
    setcolor(6);
    printf("\n\n\t\t                                M E N U                       \n");                               
    printf("\n\t\t                       -------------------------             ");                         
    printf("\n\t\t                       |  1. MAIN              |             ");                           
    printf("\n\t\t                       -------------------------             ");                               

    printf("\n\t\t                       -------------------------             ");                                
    printf("\n\t\t                       |  2. PETUNJUK          |             ");                                
    printf("\n\t\t                       -------------------------             ");                                
    
    printf("\n\t\t                       -------------------------             ");                                
    printf("\n\t\t                       |  3. TENTANG           |             ");                                
    printf("\n\t\t                       -------------------------             ");                                
 
    printf("\n\t\t                       -------------------------             ");                                
    printf("\n\t\t                       |  4. LOGOUT            |             ");                                
    printf("\n\t\t                       -------------------------             ");                                
  
    printf  ("\n\n\t\t        ===================================================\n");
    printf ("\n\t\t                      Masukkan pilihan Anda : ");
    scanf  ("%d", &pilihanmenu);

    // Membersihkan Layar terminal 
    system ("cls");
    
    /* Percabangan Switch dengan kondisi nilai yang disimpan pada variabel
       pilihan jika pengguna menuliskan 1 maka akan dipanggil fungsi masuk()
       jika pengguna menuliskna 2 maka akan dipanggil fungsi registrasi()    */
    switch (pilihanmenu){
    case 1:
        // Jika pengguna menginput angka 1 maka dipanggil fungsi main_game
        main_game();
        break;
    case 2:
        // Jika pengguna menginput angka 2 maka dipanggil fungsi petunjuk
        menu_petunjuk();
        break;
    case 3:
        // Jika pengguna menginput angka 3 maka dipanggil fungsi tentang
        menu_tentang();
        break;        
    case 4:
    	// Jika pengguna menginput angka 4 maka akan keluar dari program
        menu_masuk();
        break;
    default:
        error_alert();
        // Kembali ke label mnmasuk jika terjadi kesalahan dalam menginput pilihan
        goto menu;
        break;
    }
}

//=======================================================================//
//*************   Fungsi Untuk Menampilkan Menu Petunjuk   **************//
//=======================================================================//
// Nama Fungsi    : -                                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menampilkan menu petunjuk cara memainkan game ini    //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 20-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//

void menu_petunjuk() {
	int i, j, k, level;
    char key;

    system("cls");
	simbol();
	setcolor(14);
	printf("\n\t\t                               P E T U N J U K                       ");                      
    printf("\n\t\t                      G A M E  P U Z Z L E  N U M B E R         \n");
    printf("\n\t\t     ----------------------------------------------------------------    ");
	printf("\n\t\t        ==============================================================\n");
	printf("\t\t        || Mainkan Puzzle dan Susunlah Menjadi Urutan Yang Benar!   ||\n");
	printf("\t\t        || Geser Kotak Kosong Hingga Berurutan Seperti Dibawah Ini! ||\n");
	printf("\t\t        ==============================================================\n\n");
    initField(0);
    printf("\t\t\t\t\t   ");
    for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    for (i = 0; i<=(fieldSize - 1); i++) {
    	printf("\t\t\t\t\t   ");
        for (j= 0; j<=(fieldSize - 1); j++) {
            if (i == y && j == x) {
                printf("| %c  ", field2[i][j]);
            } else {
                printf("| %2i ", field2[i][j]);
            }
        }
        puts("|");
		printf("\t\t\t\t\t   ");
        for(k = 1; k <= fieldSize; k++) printf("+----"); puts("+");
    }
    printf("\n\t\t        ==============================================================\n");
    printf("\t\t        ||    Gunakan Tombol Panah Untuk Menggeser Kotak Kosong :   ||\n");
    printf("\t\t        ||                                                          ||\n");
    printf("\t\t        ||    1. Panah Kanan  = Menggeser Ke Kanan                  ||\n");
    printf("\t\t        ||                                                          ||\n");
	printf("\t\t        ||    2. Panah Kiri   = Menggeser Ke Kiri                   ||\n");
	printf("\t\t        ||                                                          ||\n");
	printf("\t\t        ||    3. Panah Atas   = Menggeser Ke Atas                   ||\n");
	printf("\t\t        ||                                                          ||\n");
	printf("\t\t        ||    4. Panah Bawah  = Menggeser Ke Bawah                  ||\n");
	printf("\t\t        ||                                                          ||\n");
	printf("\t\t        ==============================================================\n");
	printf("\t\t        ||                                                          ||\n");
	printf("\t\t        ||         Tekan ENTER  untuk Kembali Ke Menu Utama         ||\n");
	printf("\t\t        ||                                                          ||\n");
    printf("\t\t        ==============================================================\n");
    getch();
    system("cls");
    menu();
}

//=======================================================================//
//*************   Fungsi Untuk Menampilkan Menu Tentang   ***************//
//=======================================================================//
// Nama Fungsi    : -                                                    //
// Input Argumen  : -                                                    //
// Output Argumen : -                                                    //
// Deskripsi      : Menampilkan info tentang game puzzle ini             //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 20-12-2021                               Tgl: -               //
// Ida Bagus Mas Manuaba - 2105551008                                    //
// Kelas A                                                               //
//=======================================================================//

void menu_tentang () {
	simbol();
	setcolor(14);
	printf("\n\t\t                               T E N T A N G                       ");                      
    printf("\n\t\t                      G A M E  P U Z Z L E  N U M B E R         \n");
    printf("\n\t\t     ----------------------------------------------------------------    ");
    setcolor(6);                            
    printf("\n\t\t       ------------------------------------------------------------              ");                         
    printf("\n\t\t      |  Game Puzzle Number adalah program game susun puzzle angka |             ");
	printf("\n\t\t      |  sederhana yang kami buat untuk melatih logika dan kecepa- |             ");  
	printf("\n\t\t      |  tan berpikir pemain serta dapat dijadikan media hiburan   |             ");       
	printf("\n\t\t      |  dikala kebosanan melanda.                                 |             ");                  
    printf("\n\t\t       ------------------------------------------------------------              ");      
    printf  ("\n\t\t        ===========================================================\n");
	printf  ("\t\t         ||         P R O G R A M  D I B U A T  O L E H :       ||\n");
	printf  ("\t\t         ||                                                     ||\n");
	printf  ("\t\t         ||    1. IDA BAGUS MAS MANUABA    (2105551008)         ||\n");
	printf  ("\t\t         ||                                                     ||\n");
	printf  ("\t\t         ||    2. I PUTU AGUS PUTRA NEGARA (2105551044)         ||\n");
	printf  ("\t\t         ||                                                     ||\n");
	printf  ("\t\t         =========================================================\n");
	printf  ("\t\t         ||                                                     ||\n");
	printf  ("\t\t         ||       Tekan ENTER  untuk Kembali Ke Menu Utama      ||\n");
	printf  ("\t\t         ||                                                     ||\n");
    printf  ("\t\t         =========================================================\n");
	getch ();
    system ("cls");
    menu();                             
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
	setcolor(4);
    printf("\t\t           |================================================|\n");
  	printf("\t\t           |               PILIHAN TIDAK TERSEDIA           |\n");
  	printf("\t\t           |                                                |\n");
  	printf("\t\t           |     SILAHKAN MEMILIH PILIHAN YANG SUDAH ADA    |\n");
  	printf("\t\t           |================================================|\n");
}

void simbol(){
	setcolor(6);
    printf("\n\t\t                                  ~'.'~                            ");                           
    printf("\n\t\t                    ..          ' '.'.'.'          ..              ");                           
    printf("\n\t\t             ~ ~ ~.'  '. ~ ~ .'.'.'.'.'.'.'. ~ ~ .'  '.~ ~ ~        ");                   
    printf("\n\t\t       ~ ~ ~ ~ ~ ~.'  '. ~ ~ .'.'.'.'.'.'.'. ~ ~ .'  '.~ ~ ~ ~ ~ ~ \n");
		
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
    simbol();
	setcolor(14);
	printf("\n\t\t    S E L A M A T   D A T A N G  D I  G A M E  P U Z Z L E  N U M B E R     ");                      
    printf("\n\t\t    S I L A H K A N  L O G I N/R E G I S T E R  U N T U K  B E R M A I N  \n");
    printf("\n\t\t     ----------------------------------------------------------------       ");
    setcolor(6);
    printf("\n\n\t\t                M E N U  L O G I N/R E G I S T E R                      \n");                               
    printf("\n\t\t                       -------------------------             ");                         
    printf("\n\t\t                       |  1. LOGIN             |             ");                           
    printf("\n\t\t                       -------------------------             ");                               
    printf("\n\t\t                       -------------------------             ");                                
    printf("\n\t\t                       |  2. REGISTER          |             ");                                
    printf("\n\t\t                       -------------------------             ");                                
    printf("\n\t\t                       -------------------------             ");                                
    printf("\n\t\t                       |  3. EXIT              |             ");                                
    printf("\n\t\t                       -------------------------             ");                                                             
    printf  ("\n\t\t        ===================================================\n");
    printf ("\t\t                      Masukkan pilihan Anda : ");
    scanf  ("%d", &pilihanmasuk);
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
    simbol();
	setcolor(14);
	printf("\n\t\t                      M E N U  R E G I S T E R     ");                      
    printf("\n\t\t       S I L A H K A N  L E N G K A P I  D A T A  D I B A W A H  \n");
    printf("\n\t\t     ----------------------------------------------------------------       ");
    setcolor(6);
    printf("\n\n\t\t                          R E G I S T E R                      \n");                               
    printf("\n\t\t                       -------------------------                 \n\n");
	getchar();                         
    printf("\t\t                    |  Masukan Nama     : ");
	gets(u.nama);                                                                                         
    printf("\t\t                    |  Masukan Username : ");
	scanf("%s", u.username);                                                              
    printf("\t\t                    |  Masukan Password : "); 
	scanf("%s", u.password);                               
                                                            
    // Menuliskan nama yang diinput oleh pengguna kedalam file "RecordLogin.txt"
	fwrite(&u, sizeof(u), 1, regis);
  	fclose(regis);
  	printf("\t\t          |===================================================|\n");
  	printf("\t\t          |                    BERHASIL REGISTER              |\n");
  	printf("\t\t          |---------------------------------------------------|\n");
  	printf("\t\t          |HALLO %s!                                   \n", u.nama);
  	printf("\t\t          |AKUN ANDA TELAH TERDAFTAR,SILAHKAN LOGIN DAN BERSENANG-SENANG ");
  	printf("\t\t          |===================================================|\n");
  	getchar();
  	printf("\t\t          |             TEKAN ENTER UNTUK MELANJUTKAN         |\n");
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
    simbol();
	setcolor(14);
	printf("\n\t\t                        M E N U  L O G I N          ");                      
    printf("\n\t\t      S I L A H K A N  L O G I N  D E N G A N  A K U N  A N D A  \n");
    printf("\n\t\t     ----------------------------------------------------------------       ");
    setcolor(6);
    printf("\n\n\t\t                             L O G I N                      \n");                               
    printf("\n\t\t                       -------------------------                 \n\n");                                                                                      
    printf("\t\t                    |  Masukan Username : ");
	scanf("%s", username);                                                              
    printf("\t\t                    |  Masukan Password : "); 
  	scanf("%s", password);    
    system("cls");
    // Membeaca file "RecordLogin.txt"
    while(fread(&u,sizeof(u),1,record)){
        /*  Mengkomparasi username serta password yang diinput pengguna kedalam fungsi
            masuk() dengan username serta password yang sudah terdaftar */
        if(strcmp(username, u.username)==0 && strcmp(password, u.password)==0){
        	setcolor(2);
            printf("\t\t           |================================================|\n");
            printf("\t\t           |                                                |\n");
      		printf("\t\t           |                   LOGIN BERHASIL               |\n");
      		printf("\t\t           |                                                |\n");
      		printf("\t\t           |================================================|\n");
      		menu();
      		
        }
        //  Jika akun tidak terdaftar maka akan diberikan pilihan untuk mendaftar atau keluar dari program
        else {
        	setcolor(4);
            printf("\t\t           |================================================|\n");
            printf("\t\t           |                                                |\n");
      		printf("\t\t           |               AKUN TIDAK TERDAFTAR             |\n");
      		printf("\t\t           |                                                |\n");
      		printf("\t\t           |================================================|\n");

            mnmasuk:
            setcolor(6);
			printf("\n\t\t    S E L A M A T   D A T A N G  D I  G A M E  P U Z Z L E  N U M B E R     ");                      
    		printf("\n\t\t    S I L A H K A N  L O G I N/R E G I S T E R  U N T U K  B E R M A I N  \n");
    		printf("\n\t\t     ----------------------------------------------------------------       ");
    		
    		printf("\n\n\t\t                M E N U  L O G I N/R E G I S T E R                      \n");                               
    		printf("\n\t\t                       -------------------------             ");                         
    		printf("\n\t\t                       |  1. LOGIN ULANG       |             ");                           
    		printf("\n\t\t                       -------------------------             ");                               
    		printf("\n\t\t                       -------------------------             ");                                
   			printf("\n\t\t                       |  2. REGISTER          |             ");                                
    		printf("\n\t\t                       -------------------------             ");                                
    		printf("\n\t\t                       -------------------------             ");                                
    		printf("\n\t\t                       |  3. EXIT              |             ");                                
    		printf("\n\t\t                       -------------------------             ");                                                             
    		printf  ("\n\t\t        ===================================================\n");
    		printf ("\t\t                      Masukkan pilihan Anda : ");
    		scanf  ("%d", &pilihan);
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
                printf("t\t                    |================================================|\n");
                printf("t\t                    |                                                |\n");
        		printf("t\t                    |               PILIHAN TIDAK TERSEDIA           |\n");
        		printf("t\t                    |                                                |\n");
        		printf("t\t                    |================================================|\n");
                goto mnmasuk;
            }
        }
    }
    fclose(record);
    return;
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
    printf("\n\t\t            ||---------- Tanggal: %i/%i/%i ----------||\n\n", waktu -> tm_mday, waktu -> tm_mon + 1, waktu -> tm_year + 1900);
}
