#include <stdlib.h> // memanggil seluruh library standar bahasa c
#include <time.h> // memanggil seluruh library yang mengandung waktu
#include <stdio.h> // memanggil seluruh library input output

#define atas 1 //membuat urutan atas menjadi nomor 1
#define kiri 2 //membuat urutan kiri menjadi nomor 2
#define bawah 3 //membuat urutan bawah menjadi nomor 3
#define kanan 4 //membuat urutan kanan menjadi nomor 4

#define keyUp 0x048 // untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah atas 
#define keyDown 0x050 // untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah bawah 
#define keyLeft 0x04b // untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah kiri 
#define keyRight 0x04d // untuk membuat agar game puzzle bisa digerakan menggunakan keyboard panah kanan 

#define true 1 // mendefinisikan bahwa boolean 1 adalah true 
#define false 0 // mendefinisikan bahwa boolean 0 adalah false

#define easy 10 // untuk membuat game puzzle memiliki 10 kolom
#define medium 20 // untuk membuat game puzzle memiliki 20 kolom
#define hard 30 // untuk membuat game puzzle memiliki 30 kolom

#define caption " ----------------\n// GAME PUZZLE //\n----------------\n"

#define fieldSize 4 // untuk membuat dimensi game puzzle menjadi 4

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

int acak(int i) // membuat nilai puzzle acak sebanyak 5 kali pengacakan agar nilai nya tidak sama di setiap game 
{
  int a;
  seed += 5;
  srand(seed);

  a = (rand() % i) + 1;

  return (a);
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
void initField(int movement)
{
  int arah, arahOld = -1, nPindah = movement, xOld, yOld;
  int c = 1, i, j;
  char temp;

  srand(time(NULL));
  seed = rand();
  x = y = (fieldSize - 1);

  for (i = 0; i <= (fieldSize - 1); i++)
  {
    for (j = 0; j <= (fieldSize - 1); j++)
    {
      field[i][j] = field2[i][j] = c;
      c++;
    }
  }
  field[fieldSize - 1][fieldSize - 1] = field2[fieldSize - 1][fieldSize - 1] = ' ';

  c = 0;
  while (c != nPindah)
  {
    xOld = x;
    yOld = y;
    arah = acak(4);

    if (arah != 0)
    {
      if (c != 0)
      {
        if ((arah + 2) % 4 == arahOld)
        {
          continue;
        }
      }

      switch (arah)
      {
      case atas:
        if (y > 0)
          y--;
        else
          continue;
        break;
      case kiri:
        if (x > 0)
          x--;
        else
          continue;
        break;
      case kanan:
        if (x < fieldSize - 1)
          x++;
        else
          continue;
        break;
      case bawah:
        if (y < fieldSize - 1)
          y++;
        else
          continue;
        break;
      default:
        break;
      }

      if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1))
      {
        temp = field[y][x];
        field[y][x] = field[yOld][xOld];
        field[yOld][xOld] = temp;

        c++;
        arahOld = arah % 4;
      }
      else
      {
        x = xOld;
        y = yOld;
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
void move(int arah)
{
  int xOld, yOld;
  char temp;

  xOld = x;
  yOld = y;

  switch (arah)
  {
  case atas:
    if (y > 0)
      y--;
    break;
  case kiri:
    if (x > 0)
      x--;
    break;
  case kanan:
    if (x < (fieldSize - 1))
      x++;
    break;
  case bawah:
    if (y < (fieldSize - 1))
      y++;
    break;
  default:
    break;
  }

  if (x >= 0 && y >= 0 && x <= (fieldSize - 1) && y <= (fieldSize - 1))
  {
    temp = field[y][x];
    field[y][x] = field[yOld][xOld];
    field[yOld][xOld] = temp;
  }
  else
  {
    x = xOld;
    y = yOld;
  }
  generateOutput();
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
void generateOutput()
{
  int i, j, k;
  system("cls");
  puts(caption);
  puts("Tekan ESC untuk keluar / reset permainan...");
  for (k = 1; k <= fieldSize; k++)
    printf("+----");
  puts("+");

  for (i = 0; i <= (fieldSize - 1); i++)
  {
    for (j = 0; j <= (fieldSize - 1); j++)
    {
      if (i == y && j == x)
      {
        printf("| %c  ", field[i][j]);
      }
      else
      {
        printf("| %2i ", field[i][j]);
      }
    }
    puts("|");

    for (k = 1; k <= fieldSize; k++)
      printf("+----");
    puts("+");
  }
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
  int c, d;
  int match = true;

  for (c = 0; c <= (fieldSize - 1); c++)
  {
    for (d = 0; d <= (fieldSize - 1); d++)
    {
      if (field[c][d] != field2[c][d])
      {
        if (match == true)
        {
          match = false;
        }
      }
    }
  }
  return (match);
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
main()
{
  int i, j, k, level;
  char key;

  system("cls");
  puts(caption);
  puts("Mainkan puzzle dan menyusunnya menjadi urutan yang benar...");
  puts("Geser kotak kosong sehingga menjadi berurutan sbg berikut : \n");
  initField(0);
  for (k = 1; k <= fieldSize; k++)
    printf("+----");
  puts("+");
  for (i = 0; i <= (fieldSize - 1); i++)
  {
    for (j = 0; j <= (fieldSize - 1); j++)
    {
      if (i == y && j == x)
      {
        printf("| %c  ", field2[i][j]);
      }
      else
      {
        printf("| %2i ", field2[i][j]);
      }
    }
    puts("|");

    for (k = 1; k <= fieldSize; k++)
      printf("+----");
    puts("+");
  }
  puts("Gunakan tombol panah untuk menggeser kotak kosong...\n");
  puts("Tekan sembarang tombol untuk melanjutkan...");
  getch();
  for (;;)
  {
    system("cls");
    puts("Level : ");
    puts("\t1. Easy");
    puts("\t2. Medium");
    puts("\t3. Hard");
    printf("Pilih Level yang akan dimainkan : ");
    scanf("%i", &level);

    switch (level)
    {
    case 1:
      initField(easy);
      break;
    case 2:
      initField(medium);
      break;
    case 3:
      initField(hard);
      break;
    default:
      puts("Level salah!!");
      getch();
      continue;
    }

    system("cls");

    generateOutput();

    while ((key = getch()) != 27)
    {
      switch (key)
      {
      case keyUp:
        move(atas);
        break;
      case keyDown:
        move(bawah);
        break;
      case keyLeft:
        move(kiri);
        break;
      case keyRight:
        move(kanan);
        break;
      }
      if (cekUrut() == true)
      {
        puts("\nANDA MENANG!!!");
        break;
      }
    }
    if (key == 27)
    {
      printf("Apakah anda ingin keluar ?\n['y' utk keluar / 't' utk reset] : ");
      if (toupper(getchar()) == 'Y')
        break;
      else
        continue;
    }
    else
    {
      printf("Apakah anda ingin main lagi ? [y/t] : ");
      if (toupper(getchar()) == 'T')
      {
        puts("\nTerima Kasih Telah Mencoba!!!");
        getch();
        break;
      }
      else
        continue;
    }
  }
}
