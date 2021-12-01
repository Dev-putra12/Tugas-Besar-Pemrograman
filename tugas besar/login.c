#include <stdio.h>  //digunakan untuk memanggil isi yang berada di library ini
#include <stdlib.h> //digunakan agar bisa menggunakan fungsi define
#include <string.h>

int main(void)
{
    // deklarasi variabel untuk bagian login
    char username[10];
    char password[10];
    int ulang = 0;

    // fungsi untuk proses login
    for (int i = 0; i < 3; i++)
    {
        printf("\n==========Silahkan Login Untuk Melanjutkan===========\n");
        printf("\nmasukan username petugas : \n");
        scanf("%s", username);
        printf("Masukan Password Petugas : \n");
        scanf("%s", password);

        // menetapkan data yang digunakan untuk login
        if ((strcmp(username, "admin") == 0) && (strcmp(password, "admin") == 0))
        {
            break;
        }
        else
        {
            printf("Maaf password atau username anda salah,silahkan coba lagi!!!\n");
            ulang = ulang + 1;
        }
    }
    if (ulang < 3)
    {
        // diisi kondisi yang bisa dijalankan setelah user login
        printf("Anda berhasil login\n");
    }
    else // ini berfungsi jika user tidak login maka akan muncul pesan seperti ini
    {
        printf("\nMaaf Anda sudah melebihi batas percobaan login, silahkan login kembali nanti\n");
    }
}