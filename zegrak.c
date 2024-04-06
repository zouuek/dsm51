/*
jeœli to czytasz to jesteœ w œpi¹czce od 20 lat, próbujemy nowej metody.
Nie wiemy gdzie w twoim œnie pojawi siê ta wiadomoœæ.
Rodzina têskni.
ZbudŸ siê.
*/

#include <8051.h>    // :)
#define FALSE 0
#define TRUE 1
#define dwiescie_dwadziescia_szesc 226
#define dziewiencsetszzzesciesiot 960
#define lewa 4
#define PRAWA 16
#define duuuul 32

/*
A kiedy przyjdzie tak¿e po mnie
Zegarmistrz œwiat³a purpurowy
By mi zabe³taæ b³êkit w g³owie
To bêdê jasny i gotowy
*/

//deklaracja niepodleg³oœci

unsigned char timer_buf;
__bit __at (0x97) LED;
__bit t0_flag;
__bit __at (0x96) SEG_OFF;

__code unsigned int wzory[10] = { 0b0111111, 0b0000110,
                0b1011011, 0b1001111, 0b1100110, 0b1101101,
                0b1111101, 0b0000111, 0b1111111, 0b1101111 };

__xdata unsigned char * wyswietlacz = (__xdata unsigned char *) 0xFF30;
__xdata unsigned char * segment = (__xdata unsigned char *) 0xFF38;
unsigned char CZAS[6];
unsigned char sekunda = 0, minuta = 0, godzina = 0;
unsigned short int t0_int_cnt = 0;
unsigned char wybrany_wyswietlacz = 1, wybrany_segment = 0;
unsigned char nacisnienty = 0;
unsigned char klawisz = 0;
unsigned char klawisze[4] = {0,0,0,0};
unsigned char pamienc = 0;
unsigned char popszedni = 0;
unsigned char aktualny_klawisz = 0;
//moje funkcje o_O
void t0_serv(void);
void odswiez_wyswietlacze(void);
void uwaga_przeliczam_czas(void);
void obruc_w_lewo(void);
void inkrementuj_wybrany_segment(void);
void zainicjalizuj_caly_zbior_zmiennych_przecinek_bitow_przecinek_itp(void);
void klawa_klawa(void);
void zwienksz_sekunde(void);
void zwienksz_minute(void);
void zwienksz_godzine(void);

void main(){ //g³ówna funkcja w jêzyku ,,C''
zainicjalizuj_caly_zbior_zmiennych_przecinek_bitow_przecinek_itp();
    while(1){            // petla glowna wykonujaca sie do konca swiata i jeszcze dluzej ( tutaj taki trick, okazuje sie ze 1 mozna zamienic na inna wartosc rozna od 0 )
        if (t0_flag) {       //przerwanie zegarowe
     	    t0_flag = 0;
     	    t0_serv();
     	   	odswiez_wyswietlacze();
     	   	if(P3_5 && aktualny_klawisz == 0){
    	        klawa_klawa();
	        }
        	else if(popszedni == aktualny_klawisz && !P3_5) aktualny_klawisz = 0;

   		}
	}
}

void t0_int(void) __interrupt(1)
{
	TH0 = 226;
	t0_flag = TRUE;



}
void t0_serv(void)    // ten kod zrozumiej¹ tylko fani systemów wbudowanych
{
	if(t0_int_cnt < dziewiencsetszzzesciesiot){
	  t0_int_cnt++;
	}

	else{
    t0_int_cnt=0;
    zwienksz_sekunde();
    uwaga_przeliczam_czas();


    }
}
void odswiez_wyswietlacze(void){
    //klawisze[0] = 0;
    SEG_OFF=TRUE;
    *segment = wzory[CZAS[wybrany_segment]];
    *wyswietlacz = wybrany_wyswietlacz;
    SEG_OFF=FALSE;
    popszedni = wybrany_wyswietlacz;
    obruc_w_lewo();
    inkrementuj_wybrany_segment();
    P1_7 = !P1_7;
    
    


 /*for(i = 0, j = 1; i<6; i++, j+=j){
       SEG_OFF=TRUE;
       czass = CZAS[i];
       *wyswietlacz = 1;                    haha smieszna pentla xD
       *segment = wzory[czass];
       SEG_OFF =FALSE;
} */
}
void obruc_w_lewo(void){
    wybrany_wyswietlacz <<= 1;
    if(wybrany_wyswietlacz > 32) wybrany_wyswietlacz = 1;

}
void uwaga_przeliczam_czas(void){

    CZAS[0]=sekunda%10;            // naszym czas[0] bêd¹ jednoœci sekund które obliczamy w nastêpuj¹cy sposób: sekundê któr¹ inkrementuhemmy w opsludze przerwwanai dzielimy M O D U L O przez 10 czyli wynik nam wyjdzie od 0 do 9 czyli gitara gra ; )
    CZAS[1]=sekunda/10;            // to samo tylko dzielenie Z W Y K L E ( tez wyjdzie od 0 do 9 ;P ) no i spoko wszystko fajnie smiga
    CZAS[2]=minuta%10;             // lezy jak ula³
    CZAS[3]=minuta/10;             // smiga az milo
    CZAS[4]=godzina%10;            // bangla az chce sie zyc
    CZAS[5]=godzina/10;            // hula jak hoolahop xDD
}
void inkrementuj_wybrany_segment(void){
  wybrany_segment++;
  if(wybrany_segment > 5) wybrany_segment = 0;
}
void zainicjalizuj_caly_zbior_zmiennych_przecinek_bitow_przecinek_itp(void){
    TMOD = 0b01110000;
    TH0 = dwiescie_dwadziescia_szesc;
    t0_flag = FALSE;
    ET0 = TRUE;
    TR0 = TRUE;
    EA  = TRUE;
	SEG_OFF = TRUE;
	uwaga_przeliczam_czas();
}
void klawa_klawa(void){   // gra s³ów w nazwie funkcji :D

     //if (!nacisnienty){     haha boolem prubowal xD
        aktualny_klawisz = popszedni;
        if(aktualny_klawisz == lewa){
            //nacisnienty = 1;
            zwienksz_sekunde();
            uwaga_przeliczam_czas();
            //nacisnienty = 1;
        }
        else if (aktualny_klawisz == PRAWA){
            zwienksz_minute();
            uwaga_przeliczam_czas();
            //nacisnienty = 1;

        }
        else if (aktualny_klawisz == duuuul){
            zwienksz_godzine();
            uwaga_przeliczam_czas();
            //nacisnienty = 1;
        }

        /*
        klawisze[3] = klawisze[2];
        klawisze[2] = klawisze[1];
        klawisze[1] = klawisze[0];
        klawisze[0] = 0;
         */
}


void zwienksz_sekunde(void){   //ehh..
    sekunda++;
    if(sekunda>=60){
        sekunda = 0;
        minuta++;
        if(minuta>=60){
            minuta = 0;
            godzina++;
            if(godzina >= 24){
                godzina = 0;
                minuta = 0;
                sekunda = 0;
            }
        }
    }
}
void zwienksz_minute(void){   //ehh..
    minuta++;
    if(minuta >= 60){
        minuta = 0;
        godzina++;
        if(godzina >= 24){
            godzina = 0;
            minuta = 0;
        }
    }
}
void zwienksz_godzine(void){
    godzina++;
    if(godzina>=24){
        godzina = 0;
    }
}





/*
______________________ _______    _____________________ ________    _____ _________________________  __. __________________    _________________________  .____     
\__    ___/\_   _____/ \      \   \____    /\_   _____//  _____/   /  _  \\______   \_   _____/    |/ _| \____    /\_____  \  /   _____/\__    ___/  _  \ |    |    
  |    |    |    __)_  /   |   \    /     /  |    __)_/   \  ___  /  /_\  \|       _/|    __)_|      <     /     /  /   |   \ \_____  \   |    | /  /_\  \|    |    
  |    |    |        \/    |    \  /     /_  |        \    \_\  \/    |    \    |   \|        \    |  \   /     /_ /    |    \/        \  |    |/    |    \    |___
  |____|   /_______  /\____|__  / /_______ \/_______  /\______  /\____|__  /____|_  /_______  /____|__ \ /_______ \\_______  /_______  /  |____|\____|__  /_______ \
                   \/         \/          \/        \/        \/         \/       \/        \/        \/         \/        \/        \/                 \/        \/
        ______________________      __________ ____________________________    _______ _____.___. ___________________________________________________               
       /   _____/\__    ___/  \    /  \_____  \\______   \____    /\_____  \   \      \\__  |   | \______   \______   \____    /\_   _____/\____    /               
       \_____  \   |    |  \   \/\/   //   |   \|       _/ /     /  /   |   \  /   |   \/   |   |  |     ___/|       _/ /     /  |    __)_   /     /                
       /        \  |    |   \        //    |    \    |   \/     /_ /    |    \/    |    \____   |  |    |    |    |   \/     /_  |        \ /     /_                
      /_______  /  |____|    \__/\  / \_______  /____|_  /_______ \\_______  /\____|__  / ______|  |____|    |____|_  /_______ \/_______  //_______ \               
              \/                  \/          \/       \/        \/        \/         \/\/                          \/        \/        \/         \/               
                ____  ___       ___________                                       ________                                             ____  ___                    
___  ______  ___\   \/  /___  __\__    ___/___   _____ _____    ______________    \______ \   ___________  ____  _________________  ___\   \/  /___  ______  ___
\  \/  /\  \/  / \     / \  \/  / |    | /  _ \ /     \\__  \  /  ___/\___   /     |    |  \ /  _ \_  __ \/  _ \/  ___/\___   /\  \/  / \     / \  \/  /\  \/  /    
 >    <  >    <  /     \  >    <  |    |(  <_> )  Y Y  \/ __ \_\___ \  /    /      |    `   (  <_> )  | \(  <_> )___ \  /    /  >    <  /     \  >    <  >    <
/__/\_ \/__/\_ \/___/\  \/__/\_ \ |____| \____/|__|_|  (____  /____  >/_____ \ /\ /_______  /\____/|__|   \____/____  >/_____ \/__/\_ \/___/\  \/__/\_ \/__/\_ \    
      \/      \/      \_/      \/                    \/     \/     \/       \/ \/         \/                        \/       \/      \/      \_/      \/      \/



*/

