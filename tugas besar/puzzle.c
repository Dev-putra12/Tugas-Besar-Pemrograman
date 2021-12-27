#include <stdlib.h> 																// memanggil seluruh library standar bahasa c
#include <time.h> 																// memanggil seluruh library yang mengandung waktu
#include <stdio.h> 																// memanggil seluruh library input output
#include <windows.h>																// memanggil seluruh library yang tersedia di windows.h
#include <string.h>																// memanggi seluruh library string.h

#define atas 1 																	//membuat urutan atas menjadi nomor 1
#define kiri 2 																	//membuat urutan kiri menjadi nomor 2
#define bawah 3 																//membuat urutan bawah menjadi nomor 3
#define kanan 4 																//membuat urutan kanan menjadi nomor 4

#define keyUp 0x048																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah atas 
#define keyDown 0x050 																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah bawah 
#define keyLeft 0x04b 																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah kiri 
#define keyRight 0x04d																// untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah kanan 

#define true 1 																	// mendefinisikan bahwa boolean 1 adalah true 
#define false 0 																// mendefinisikan bahwa boolean 0 adalah false

#define easy 2 																	// untuk membuat game puzzle memiliki 10 kolom
#define medium 10 																// untuk membuat game puzzle memiliki 20 kolom
#define hard 20 																// untuk membuat game puzzle memiliki 30 kolom

#define fieldSize 4 																// untuk membuat dimensi game puzzle menjadi 4

char field[fieldSize][fieldSize]; // untuk menentukan baris
char field2[fieldSize][fieldSize]; // untuk menentukan kolom
unsigned int seed; // digunakan agar tidak ada angka yang bernilai negatif 
int x, y; // mendeklarasikan variabel x dan y 

int acak(int i); // untuk membuat nilai acak pada kolom puzzle
void initField(int movement); // untuk membuat pergerakan di dalam game puzzle 
void move(int arah); // untuk menentukan arah gerak pada game puzzle
void generateOutput(); // untuk membuat tampilan output pada game puzzle 
int cekUrut(); // untuk melakukan pengecekan apakah nilai sudah urut agar puzzle bisa tau benar atau salah

//=======================================================================//
//***************  Fungsi Untuk Mengacak Nomor  *****************		 //
//=======================================================================//
// Nama Fungsi    : acak                                           		 //
// Input Argumen  : int acak(int i)                                      //
// Output Argumen : -                                                    //
// Deskripsi      : untuk melakukan pengacakan nilai pada game puzzle    //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 2o-12-2021                               Tgl: -               //
// I Putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//

// fungsi ini adalah untuk melakukan pengacakan kepada nilai nilai dari puzzle agar permainan puzzle angka menjadi lebih menarik 
int acak(int i) 
{
    int a; 																	// variabel a yang memiliki tipe data integer
    seed += 5; 																	//nilai seed ditambah 5
    srand(seed); 																//melakukan pengacakan random dari nilai seed 

    a = (rand() % i) + 1;															//variabel a menyimpan nilai angka random yang dimoduluskan dengan i dan ditambah 1

    return(a);																	//nilai dikembalikan ke variabel a
}

//=======================================================================//
//***************  Fungsi Untuk Pergerakan puzzle  *****************	 //
//=======================================================================//
// Nama Fungsi    : initField                                            //
// Input Argumen  : void initField(int movement)                         //
// Output Argumen : -                                                    //
// Deskripsi      : untuk mengatur pergerakan pada game puzzle     		 //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 2o-12-2021                               Tgl: -               //
// I Putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//
//fungsi initfield dengan parameter movement bertipe data integer
void initField(int movement) 
{
    int arah, arahOld = -1, nPindah = movement, xOld, yOld; 											//deklarasi variabel bertipe data integer
    int c = 1, i, j;																//deklarasi variabel bertipe data integer	
    char temp;																	//variabel temp bertipe data character

    srand(time(NULL));																//untuk memunculkan angka random yang polanya tidak sama seperti yang telah ditampilkan sebelumnya
    seed = rand();																//angka random akan disimpan di variabel seed
    x = y = (fieldSize - 1);															//nilai x disamadengankan nilai y disamadengankan fieldsize-1 

    for (i = 0; i <= (fieldSize - 1); i++) {													//perulangan for
        for (j = 0; j <= (fieldSize - 1); j++) {												//perulangan for
            field[i][j] = field2[i][j] = c;													//array field [i][j] sama dengan field2[i][j] sama dengan c
            c++;																//nilai c ditambah 1
        }
    }
    field[fieldSize - 1][fieldSize - 1] = field2[fieldSize - 1][fieldSize - 1] = ' ';	//array field [fieldsize-1][fieldsize-1] = field2[fieldSize - 1][fieldSize - 1]

    c = 0;																	//nilai c=0
    while (c != nPindah) 															//perulangan while apabila nilai c tidak sama dengan nilai variabel npindah
	{
        xOld = x;																//nilai xOld = x
        yOld = y;																//nilai yOld = y
        arah = acak(4);																//variabel arah menyimpan nilai fungsi acak dengan parameter nilai 4

        if (arah != 0) {															//jika nilai variabel arah tidak sama denga 0 
            if ( c != 0) {															//jika nilai variabel c tidak sama dengan 0
                if ((arah + 2) % 4 == arahOld) {												//jika nilai arah ditambah 2 dan dimoduluskan 4 sama dengan arahOld
                    continue;															//melewatkan semua perintah dibawahnya dan langsung melompat ke bagian kondisi perulangan
                }
            }

            switch (arah) {															//percabangan switch case dengan variabel arah 
                case atas :															//jika arah=atas
                    if (y > 0) y--;
                    else continue;
                    break;															//keluar dari percabangan switch case
                case kiri:															//jika arah=kiri
                    if (x > 0) x--;
                    else continue;
                    break;															//keluar dari percabangan switch case
                case kanan :															//jika arah=kanan
                    if (x < fieldSize - 1) x++;
                    else continue;
                    break;															//keluar dari percabangan switch case
                case bawah :															//jika arah=bawah
                    if (y < fieldSize - 1) y++;
                    else continue;
                    break;															//keluar dari percabangan switch case
                default :															//jika tidak
                    break;															//keluar dari percabangan switch case
            }

            if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {								//jika nilai x >= 0 dan y >= 0 dan x <= fieldSize - 1 dan y <= fieldSize - 1
                temp = field[y][x];														//variabel temp disamadengankan array field [y][x]
                field[y][x] = field[yOld][xOld];												//array field [y][x] disamadengankan array field [yOld][xOld]
                field[yOld][xOld] = temp;													//array field[yOld][xOld] disamadengankan temp

                c++;																//nilai c ditambah 1
                arahOld = arah % 4;														//variabel arahOld menyimpan nilai arah yang dimoduluskan dengan 4
            } else {																//jika tidak
                x = xOld;															//nilai x disamadengankan nilai xOld
                y = yOld;															//nilai y disamadengankan nilai yOld
            }
        }
    }
}

//=======================================================================//
//***************  Fungsi Untuk Bergerak pada game puzzle  **************//
//=======================================================================//
// Nama Fungsi    : move                                           		 //
// Input Argumen  : void move(int arah)                                  //
// Output Argumen : -                                                    //
// Deskripsi      : untuk membuat cara bergerak pada game puzzle agar 	 //
					sesuai dengan pergerakan yang sudah ada     	     //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 2o-12-2021                               Tgl: -               //
// I Putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//
//fungsi move dengan bertipe data integer dengan parameter bertipe data integer
void move(int arah) 																	
{
    int xOld, yOld;																//variabel xOld dan Yold bertipe data integer
    char temp;																	//variabel temp bertipe data char

    xOld = x;																	//nilai xOld = x
    yOld = y;																	//nilai yOld = y

    switch (arah) {																//switch case arah
        case atas :																//jika arah = atas
            if (y > 0) y--;															//jika nilai y > 0, nilai y dikurangi 1 
            break;																//keluar dari swtich case
        case kiri:																//jika arah = kiri 
            if (x > 0) x--;															//jika nilai x > 0, nilai x dikurangi 1
            break;																//keluar dari switch case
        case kanan :																//jika arah = kanan
            if (x < (fieldSize - 1)) x++;													//jika nilai x < fieldsize-1, nilai x ditambah 1 
            break;																//keluar dari switch case 
        case bawah :																//jika arah = bawah 
            if (y < (fieldSize - 1)) y++;													//jika nilai y < fieldsize-1, nilai y ditambah 1
            break;																//keluar dariu switch case
        default :																//jika tidak
            break;																//keluar dari switch case
    }

    if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1)) {									//jika nilai x >=0 dan y>=0 dan x <= fieldsize-1 dan y<=fieldsize-1 
        temp = field[y][x];															//variabel temp disamadengankan field[y][x]
        field[y][x] = field[yOld][xOld];													//array field[y][x] disamadengankan array field[yOld][xOld]
        field[yOld][xOld] = temp;														//array field[yOld][xOld] disamadengankan temp
    } else {																	//jika tidak
        x = xOld;																//nilai x disamadengankan xOld
        y = yOld;																//nilai y disamadengankan yOld
    }
    generateOutput();																//memanggil fungsi generateOutput
}

//=======================================================================//
//*****  Fungsi Untuk Membuat output garis hiasan untuk puzzle  ******   //
//=======================================================================//
// Nama Fungsi    : generateOutput                                       //
// Input Argumen  : void generateOutput()                                //
// Output Argumen : -                                                    //
// Deskripsi      : untuk membuat output garis pinggir pada puzzle dan 	 //
					membuat output tulisan petunjuk     				 //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 2o-12-2021                               Tgl: -               //
// I Putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//
//fungsi generateOutput yang menampilkan tampilan saat user sudah login
void generateOutput() 
{
    int i, j, k;																						//membuat variabel dengan tipe data integer
    system ("cls");																						//untuk membersihkan layar
	simbol();																							//untuk memanggil fungsi simbol
	setcolor(14);																						//untuk menggunakan warna dengan kode warna 14
	printf("\n\t\t                         A Y O  S E L E S A I K A N                       ");         					//untuk menampilkan tulisan didalam tanda petik             
    printf("\n\t\t                      G A M E  P U Z Z L E  N U M B E R         \n");								//untuk menampilkan tulisan didalam tanda petik  
    printf("\n\t\t                               L E V E L  %d                     \n", level);							//untuk menampilkan tulisan didalam tanda petik  
    printf("\n\t\t     ----------------------------------------------------------------    ");							//untuk menampilkan tulisan didalam tanda petik  
	printf("\n\t\t        ==============================================================\n");						//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t        ||  Mainkan Puzzle dan Susunlah Menjadi Urutan Yang Benar!  ||\n");							//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t        ||   Geser Kotak Kosong Hingga Menjadi Angka Yang Berurut   ||\n");							//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t        ==============================================================\n\n");						//untuk menampilkan tulisan didalam tanda petik  
	printf("\t\t\t\t\t   ");																			//untuk menampilkan tulisan didalam tanda petik  
    for(k = 1; k <= fieldSize; k++) 																	//perulangan for
	printf("+----"); 																					//menampilkan teks dalam tanda kutip
	puts("+");																							//menampilkan teks dalam tanda kutip disertai perpindahan

    for (i = 0; i<=(fieldSize - 1); i++) {																//perulangan for
    	printf("\t\t\t\t\t   ");																		//menampilkan teks dalam tanda kutip
        for (j= 0; j<=(fieldSize - 1); j++) {													//perulangan for	
            if (i == y && j == x) {																		//jika i = y dan j = x
                printf("| %c  ", field[i][j]);													//untuk menampilkan teks bertipe data char dari array field[i][j]
            } else {																					//jika tidak
                printf("| %2i ", field[i][j]);													//untuk menampilkan teks bertipe data integer dari array field[i][j]
            }
        }
        puts("|");																						//menampilkan teks dalam tanda kutip disertai dengan perpindahan baris
		printf("\t\t\t\t\t   ");																		//menampilkan teks dalam tanda kutip
        for(k = 1; k <= fieldSize; k++) 																//perulangan for
		printf("+----"); 																				//menampilkan teks dalam tanda kutip
		puts("+");																						//menampilkan teks dalam kutip dengan perpindahan baris
    }
	puts    ("\n\t\t   || -------- Tekan ESC untuk Keluar / Reset Permainan . . . -------- ||\n");						//menampilkan teks dalam kutip dengan perpindahan baris
}

//=======================================================================//
//***************  Fungsi Untuk Mengecek Urutan  *****************		 //
//=======================================================================//
// Nama Fungsi    : cekUrut                                              //
// Input Argumen  : int cekUrut()                                      	 //
// Output Argumen : -                                                    //
// Deskripsi      : untuk mengecek urutan nilai pada game puzzle    	 //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 2o-12-2021                               Tgl: -               //
// I Putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//
int cekUrut() 																							
{
    int c, d;																							//variabel bertipe data integer
    int match = true;																					//variabel match = true bertipe data integer

    for (c = 0; c <= (fieldSize - 1); c++) {													//perulangan for
        for (d = 0; d <= (fieldSize - 1); d++) {												//perulangan for
            if (field[c][d] != field2[c][d]) {													//jika array field[c][d] tidak sama dengan array field2[c][d]
                if (match == true) {														//jika match = true
                    match = false;																		//jika match = false
                }
            }
        }
    }
    return(match);																						//mengembalikan nilai ke variabel match
}

//=======================================================================//
//***************  Fungsi Untuk Program Utama *****************		 	 //
//=======================================================================//
// Nama Fungsi    : main                                           		 //
// Input Argumen  : main()                                      		 //
// Output Argumen : -                                                    //
// Deskripsi      : untuk menjalankan keseluruhan program pada  		 //
					game puzzle    										 //
//                                                                       //
// Versi : 1.0                                      Rev. 0               //
// Tgl   : 2o-12-2021                               Tgl: -               //
// I Putu Agus Putra Negara - 2105551044                                 //
// Kelas B                                                               //
//=======================================================================//
						
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
//fungsi ini unutk memilih level kesulitan pada game puzzle 
void main_game() 
{
	int i, j, k;																						//variabel bertipe data integer
    char key;																							//variabel key bertipe data char
    for(;;) {																							//menggunakan for
    simbol();																							//memanggil fungsi simbol
	setcolor(14);																						//setting agar menggunakan warna dengan kode 14
	printf("\n\t\t    S E L A M A T   D A T A N G  D I  G A M E  P U Z Z L E  N U M B E R");            			//untuk menampilkan teks didalam tanda petik          
    printf("\n\t\t                 S I L A H K A N  P I L I H  L E V E L\n");							//untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t     ----------------------------------------------------------------    ");					//untuk menampilkan teks didalam tanda petik 
    setcolor(6);																						//untuk setting agar menggunakan warna dengan kode 6
    printf("\n\n\t\t                          P I L I H  L E V E L                       \n");          			//untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t                       |  1. EASY              |             ");                      			//untuk menampilkan teks didalam tanda petik      
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik          
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       |  2. MEDIUM            |             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       |  3. HARD              |             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       |  4. KEMBALI           |             ");                      			//untuk menampilkan teks didalam tanda petik           
    printf("\n\t\t                       -------------------------             ");						//untuk menampilkan teks didalam tanda petik 
    printf("\n\n\t\t        ===================================================\n");						//untuk menampilkan teks didalam tanda petik 
    printf("\n\t\t                      Masukkan pilihan Anda : ");								//untuk menampilkan teks didalam tanda petik 
    scanf ("%d", &level);													//untuk penggunakan memasukan level yang dipilih
    system("cls");														//membersihkan layar


        switch (level) {													//switch case
            case 1 :														//jika case 1 adalah easy
                initField(easy);												//memanggil field easy
                break;														//keluar dari switch case
            case 2 :														//jika case 2 adalah medium
                initField(medium);												//memanggil field medium
                break;														//keluar dari switch case
            case 3 :														//jika case 3 adalah hard
                initField(hard);												//memanggil field hard
                break;														//keluar dari switch case
            case 4 :														//jika case 4 adalah menu
                menu();														//memanggil function menu
                break;														//keluar dari switch case
            default :														//jika tidak
                puts("\n\t\t                       ------------------------------             ");       			//menampilkan teks dalam kutip dengan perpindahan baris                  
    			puts("\n\t\t             	       |LEVEL YANG ANDA PILIH SALAH |             ");			//menampilkan teks dalam kutip dengan perpindahan baris
				puts("\n\t\t             	       |MASUKKAN LEVEL YANG TERSEDIA|             ");       	//menampilkan teks dalam kutip dengan perpindahan baris
    			puts("\n\t\t                       ------------------------------             ");			//menampilkan teks dalam kutip dengan perpindahan baris
                getch();													//menahan tampilan pada layar
                continue;													//melewatkan semua perintah dibawahnya dan langsung melompat ke bagian kondisi perulangan
        }
        
        system("cls");														//membersihkan layar

        generateOutput();													//memanggil fungsi generateOutput

        while ((key = getch()) != 27) {												//kondisi while
            switch(key) {													//switch key 
                case keyUp :													//jika switch key atas
                    move(atas);													//move ke atas
                    break;													//keluar dari case
                case keyDown :													//jika keyDown
                    move(bawah);												//move kebawah
                    break;													//keluar dari case
                case keyLeft :													//jika keyLeft
                    move(kiri);													//move ke kiri
                    break;													//keluar dari case
                case keyRight :													//jika keyRight
                    move(kanan);												//move ke kanan
                    break;													//keluar dari case
            }
            if (cekUrut() == true) {												//jika cekUrut = true
                puts("\n\t\t                       -------------------------             ");            			//menampilkan teks dalam kutip dengan perpindahan baris             
    			puts("\n\t\t             	       |SELAMAT, ANDA MENANG!!!|             ");            		//menampilkan teks dalam kutip dengan perpindahan baris               
    			puts("\n\t\t                       -------------------------             "); 				//menampilkan teks dalam kutip dengan perpindahan baris
                break;														//keluar dari while 
            }
        }
        if (key == 'q') {													//jika key q ditekan
            printf("Apakah anda ingin keluar ?\n['y' utk keluar / 't' utk reset] : \n");					//untuk menampilkan teks didalam tanda petik
            if (toupper(getchar()) == 'Y') break;														
            else continue;
        } else {
        	printf("\n\t\t   	|| -------- Silahkan Pilih Level Untuk Tetap Bermain -------- ||\n");			//untuk menampilkan teks didalam tanda petik
            if (toupper(getchar()) == 'T') {
                puts("\nTerima Kasih Telah Mencoba!!!");									//untuk menampilkan teks didalam tanda petik dengan perpindahan baris
                getch();													//untuk menahan tampilan 
                break;														//untuk kelaur dari kondisi if else
            }
            else continue;
        }
    }
}
