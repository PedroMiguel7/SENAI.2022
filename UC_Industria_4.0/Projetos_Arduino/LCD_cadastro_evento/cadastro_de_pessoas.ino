#include <Keypad.h>

#include <LiquidCrystal.h>
#include <string.h>
LiquidCrystal lcd(12, 11, 5, 4, 13, 10);

int mostrando = 0;
int listar = 0;
int participantes = 0;

char alpha[] = "abcdefghijklmnopqrstuvwxyz";
char nomes[100][7];
char nome[] = "aaaaaa";
char buscar[7];
char orig[7];
char mod[7];

char menu[4][10] = {"Evento", "Novo Part", "Listar", "Buscar"};
int idades[100];

int dia_hoje = 02;
int mes_hoje = 04;
int ano_hoje = 2022;
int data_evento[3];

// Definindo os pinos digitais que serão usados:
int bt_voltar = 6;
int bt_menos = 7;
int bt_mais = 8;
int bt_enter = 9;

void setup() // Tela de Boot
{  
  	pinMode(bt_mais, INPUT);
  	pinMode(bt_menos, INPUT);
  	pinMode(bt_enter, INPUT);
  	pinMode(bt_voltar, INPUT);
 
  	lcd.begin(16, 2);
  	lcd.print("-- Desafio 01 --");
  	lcd.setCursor(0, 1);
  	lcd.print("Iniciando");
  	for (int i = 0; i < 3; i++)
  	{
  		lcd.print(".");
    	delay(300);
  	}
  	delay(200);
  	lcd.clear();
}

// Função para ficar mais fácil de alterar quando mudar para teclado USB
int lerBotao(int botao) 
{
  	return digitalRead(botao);
} 

int mostrarMenu()
{
  	mostrando = 0;
	while (1) // Mostrando o MENU
 	{
   		delay(200);
   		lcd.clear();
      	lcd.setCursor(0,0);

      	// Lendo os Inputs dos botões
   		int bmais = lerBotao(bt_mais);
  	 	int bmenos = lerBotao(bt_menos);
  		int benter = lerBotao(bt_enter);
      
   		if (bmais == 1 && mostrando != 0) mostrando--;
   		if (bmenos == 1 && mostrando != 3) mostrando++;
   		if (benter == 1)
   		{
     		if (mostrando == 0) return 1;       // Cadastrar eventos
     		else if (mostrando == 1) return 2;  // Cadastrar participantes
       		else if (mostrando == 2) return 3;  // Listar participantes
   			else if (mostrando == 3) return 4;  // Buscar
        }
		
      	// Imprimindo o Menu
      	for (int i = mostrando; i <= mostrando+1; i++)
        {       	
          	// Se Caso o próximo indice não exista, encerre
          	if (i >= sizeof(menu)/10) break;
          	
          	if (mostrando == 0) // Imprimindo o cabeçalho do menu
            {
      			lcd.print("  -=- MENU -=-");
      			lcd.setCursor(0,1); 
            }
          
          	// Mostrando os < > quando elemento selecionado e imprimindo o numero do menu
          	if (mostrando == i) lcd.print("<"); else lcd.print(" ");
          	lcd.print(i+1);
          	if (mostrando == i) lcd.print("> - "); else lcd.print("  - ");
                   	
          	// Imprimindo a opção do menu (Ex: Listar, Novo Part...)
          	for (int j = 0; j < strlen(menu[i]); j++)
            {
             	lcd.print(menu[i][j]); 
            }
          
          	// Se mostrando for 0, ele só vai imprimir uma opção, por causa do cabeçalho
          	if(mostrando == 0) break;
          	lcd.setCursor(0,1);
        }
    } 
}

void recebeData(int dat[3]) // Recebe um vetor para fazer o retorno por parâmetros
{
    int editando = 1;
    int dia_evento = dia_hoje;
    int mes_evento = mes_hoje;
    int ano_evento = ano_hoje;
 
    while(1) // Recebendo a data do evento
    {
        delay(200);
        lcd.clear();
        lcd.setCursor(0, 0);
  	    lcd.print("Dia do Evento:");
        lcd.setCursor(0, 1);
    
        // Lendo os Imputs dos botões
        int bmais = lerBotao(bt_mais);
        int bmenos = lerBotao(bt_menos);
        int benter = lerBotao(bt_enter);
        int bvoltar = lerBotao(bt_voltar);

        // Configurando os botões de voltar e avançar
        if (bvoltar == 1 && editando != 1) editando--;
        if (benter == 1) editando++;
      
      	// Se Editando foi maior que 3, é pq ele já acabou de editar o ano
        if (editando > 3) 
        {
          	dat[0] = dia_evento;
          	dat[1] = mes_evento;
          	dat[2] = ano_evento;
          	
          	if (validaData(dat) == 1) recebeData(dat);
          	break;
        }

	    if (editando == 1) // editar dia
        {
            if (bmais == 1) dia_evento++;
            else if (bmenos == 1) dia_evento--;
      
            if (dia_evento > 30) dia_evento = 1;
            if (dia_evento < 1) dia_evento = 30;
        }
    
        else if (editando == 2) // editar mês
        {
            if (bmais == 1) mes_evento++;
            else if (bmenos == 1) mes_evento--;
      
            if (mes_evento > 12) mes_evento = 1;
            if (mes_evento < 1) mes_evento = 12;
        }
    
        else if (editando == 3) // editar ano
        {
            if (bmais == 1) ano_evento++;
            else if (bmenos == 1) ano_evento--;
        }
    
   	    // Imprimindo o dia
        if (editando == 1) lcd.print(" <");
        else lcd.print("  ");
        if (dia_evento < 10) lcd.print("0");
        lcd.print(dia_evento);
        if (editando == 1) lcd.print(">");
        else lcd.print(" ");

        // Imprimindo o mês
        if (editando == 2) lcd.print("<");
        else lcd.print(" ");
        if (mes_evento < 10) lcd.print("0");
        lcd.print(mes_evento);
        if (editando == 2) lcd.print(">");
        else lcd.print(" ");

        // Imprimindo o Ano
        if (editando == 3) lcd.print("<");     
        else lcd.print(" ");
        lcd.print(ano_evento); 
        if (editando == 3) lcd.print(">");
    } 
}

int validaData(int data[3])
{
  	// data[0] == dia do evento
  	// data[1] == mes do evento
  	// data[2] == ano do evento
  	lcd.clear();
  
  	// Verificando se o evento é em uma data posterior ou não
  	if ((data[2] > ano_hoje) || (data[2] == ano_hoje && data[1] > mes_hoje) || (data[2] == ano_hoje && data[1] == mes_hoje && data[0] > dia_hoje))
    {
   		lcd.print("CADASTRO FEITO!");
  		delay(1000);
      	return 0;
    }
  	else
    {
      	lcd.print("DATA INVALIDA!");
      	delay(1000);
      	return 1;
    }
}

int validaIdade(int idade) // valida se for 18+
{
  	lcd.clear();
 	if (idade >= 18) return 0;
    else
  	{
      	lcd.print("IDADE INVALIDA!");
      	delay(1000);
      	lcd.clear();
      	return 1;
    }
}

void cadastraParticipante(char nomes[100][7])
{
  	delay(250);
  	lcd.clear();
 	int idade = 18;
  
  	while(1) // Recebendo a idade da pessoa
    {   
      	delay(150);
      	lcd.setCursor(0, 0);
      	lcd.print("Idade:");

      	// Recebendo os inputs
      	int bmais = lerBotao(bt_mais);
      	int bmenos = lerBotao(bt_menos);
      	int benter = lerBotao(bt_enter);

      	if (bmais == 1) idade++;
      	else if (bmenos == 1 && idade != 1) idade--;
      	else if (benter == 1 && validaIdade(idade) == 0) break;

      	lcd.setCursor(0, 1);
      	lcd.print("   <");
      	lcd.print(idade);
      	lcd.print(" anos>");
    }
  
  	int escolha = 0;
  	int quant = 0;
  	char nome[] = "aaaaaa";
  	while (1) // Recebendo o nome da pessoa
    {
      	delay(250);
      	lcd.clear();
      	lcd.setCursor(0, 0);
      	lcd.print("Digite seu Nome:");

      	// Recebendo os inputs
      	int bmais = lerBotao(bt_mais);
      	int bmenos = lerBotao(bt_menos);
      	int benter = lerBotao(bt_enter);
      	int bvoltar = lerBotao(bt_voltar);

      	// Configurando os botões
      	if (bmais == 1) escolha++;

      	else if (bmenos == 1) escolha--;

       	else if (bvoltar == 1 && quant != 0)
        {
          	quant--;
          	for (int i = 0; i < 26; i++)
            {
              	if (alpha[i] == nome[quant]) escolha = i;
            }
        }
          
      	else if (benter == 1)
        {
          	quant++;
          	for (int i = 0; i < 26; i++)
            {
              	if (alpha[i] == nome[quant]) escolha = i;
            }

          	if (quant == 5) //armazenar nomes dos participantes
            {
              	
              	for (int i = 0; i < 6; i++)
                {
                	nomes[participantes][i] = nome[i]; 
                  	idades[i]= idade;
                }
              	participantes++;
              	lcd.clear();
              	delay(100);
              	return;
            }
        }
          
      	// Se for menor que "Z", volta para "A" e vice-versa
      	if (escolha < 0) escolha = 25;
      	if (escolha > 25) escolha = 0;
            
      	nome[quant] = alpha[escolha];
      	lcd.setCursor(0, 1);
      	lcd.print(" ");
      	for (int i = 0; i < 6; i++) // Imprimindo
        {
          	if (quant == i) lcd.print("<");
          	else lcd.print(" ");
          	lcd.print(nome[i]);
          	if(quant == i) lcd.print(">");
          	else lcd.print(" ");
        }
    } 
}

void listarParticipantes()
{
 	while (1) // Listando os participantes
    {
      	delay(350);
      	lcd.clear();
      
      	// Se não tiver nenhum dado na matriz
      	if (participantes == 0)
        {
          	lcd.print("Sem Cadastros!");
          	delay(1500);
          	return;
        }
      
      	lcd.setCursor(0, 0);
      	int bmais = lerBotao(bt_mais);
      	int bmenos = lerBotao(bt_menos);
      	int benter = lerBotao(bt_enter);
      	int bvoltar = lerBotao(bt_voltar);

      	if (bmenos == 1 && listar < participantes) listar+=2;
      	else if (bmais == 1 && listar != 0) listar-=2;
        else if (benter == 1 || bvoltar == 1) break;

       	lcd.setCursor(0,0);
      	for (int i = listar; i < listar+2; i++)
        {
          if (i < participantes){
          if (i < 9) lcd.print("0");
          lcd.print(i+1);
          lcd.print(" - ");
          lcd.print(nomes[i]);
          lcd.setCursor(0,1);
          }
        }
    }
  	delay(250);
}

void buscar_verificar() 
{
  delay(350);
  lcd.clear();    
  lcd.setCursor(0, 0);
  int escolha = 0;
  int quant = 0;
  char buscar[] = "aaaaaa";
  while (1) // Recebendo o nome da pessoa para buscar
   {
      delay(350);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Digite o Nome:");

      // Recebendo os inputs
      int bmais = digitalRead(bt_mais);
      int bmenos = digitalRead(bt_menos);
      int benter = digitalRead(bt_enter);
      int bvoltar = digitalRead(bt_voltar);

      	// Configurando os botões
      	if (bmais == 1) escolha++;

      	else if (bmenos == 1) escolha--;

       	else if (bvoltar == 1 && quant != 0)
        {
          	quant--;
          	for (int i = 0; i < 26; i++)
            {
              	if (alpha[i] == buscar[quant]) escolha = i;
            }
        }
          
      	else if (benter == 1)
        {
        	quant++;
          	for (int i = 0; i < 26; i++)
            {
              	if (alpha[i] == buscar[quant]) escolha = i;
            }
          	if (quant == 5) break;
        }
          
      	// Se for menor que "Z", volta para "A" e vice-versa
      	if (escolha < 0) escolha = 25;
      	if (escolha > 25) escolha = 0;
            
        buscar[quant] = alpha[escolha];
      	lcd.setCursor(0, 1);
      	lcd.print(" ");
      	for (int i = 0; i < 6; i++) // Imprimindo
        {
          	if (quant == i) lcd.print("<");
          	else lcd.print(" ");
          	lcd.print(buscar[i]);
          	if(quant == i) lcd.print(">");
          	else lcd.print(" ");
        }
     } 
  
  // Comparar igualdade entre buscar e nome.
  	lcd.clear();
  	lcd.setCursor(0,0);
  	for (int i=0; i<participantes; i++)
  	{
   		if (nomes[i][0] == buscar[0] && nomes[i][1] == buscar[1] && nomes[i][2] == buscar[2] && nomes[i][3] == buscar[3] &&nomes[i][4] == buscar[4] && nomes[i][5] == buscar[5]) 
        {
         	lcd.print("Nome Encontrado!");
          	delay(2000);
          
          	lcd.clear();
          	lcd.setCursor(0,0);
          	for (int j=0; j<6; j++)
            {
              	lcd.print(nomes[i][j]);
            }
          	lcd.setCursor(0,1);
          	lcd.print("Idade: ");
          	lcd.print(idades[i]);
          	delay(2000);
          	return;
        }
    }
  	lcd.print("Nao Encontrado!");
  	delay(2000);
}
                      
// Função que modifica o nome de algum participante.
/*void modificar(char orig[7], char mod[7])
{
	perdemos o código dessa parte, porque o tinkercard bugou, e essa era a última versão que consegui recuperar, sorry.
}
*/
void loop() 
{
  	lcd.clear();
    int adm = mostrarMenu();
  
  	switch (adm)
    {
     	case 1: recebeData(data_evento); break;
      	case 2: cadastraParticipante(nomes); break;
      	case 3: listarParticipantes(); break;
      	case 4: buscar_verificar(); break;
      	//case 5: Modificar(orig, mod); break;
    }
}