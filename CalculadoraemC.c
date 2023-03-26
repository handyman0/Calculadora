#include <gtk/gtk.h>

static GtkWidget *result_label;
static double num1 = 0;
static double num2 = 0;
static char operador = ' ';
static int decimal_pressed = 0;

// Função para atualizar o label do resultado
void atualiza_label_resultado() {
    char str[50];
    snprintf(str, sizeof(str), "%.2f", num2);
    gtk_label_set_text(GTK_LABEL(result_label), str);
}

// Função para atualizar os números e realizar a operação escolhida
void realizar_operacao(char op) {
    switch(operador) {
        case '+':
            num2 = num1 + num2;
            break;
        case '-':
            num2 = num1 - num2;
            break;
        case '*':
            num2 = num1 * num2;
            break;
        case '/':
            num2 = num1 / num2;
            break;
        default:
            num2 = num1;
            break;
    }
    num1 = 0;
    operador = op;
    decimal_pressed = 0;
    atualiza_label_resultado();
}

// Função para adicionar um número ao visor da calculadora
void adicionar_numero(int n) {
    if(decimal_pressed) {
        num2 += n / 10.0;
    } else {
        num2 = num2 * 10 + n;
    }
    atualiza_label_resultado();
}

// Função para adicionar um ponto decimal ao visor da calculadora
void adicionar_ponto_decimal() {
    decimal_pressed = 1;
    atualiza_label_resultado();
}

// Função para limpar os números e operador
void limpar_calculadora() {
    num1 = 0;
    num2 = 0;
    operador = ' ';
    decimal_pressed = 0;
    atualiza_label_resultado();
}

// Função chamada quando o botão de operação é pressionado
void operacao_pressao(GtkWidget *widget, gpointer data) {
    char op = *(char*)data;
    num1 = num2;
    realizar_operacao(op);
}

// Função chamada quando o botão de número é pressionado
void numero_pressao(GtkWidget *widget, gpointer data) {
    int n = *(int*)data;
    adicionar_numero(n);
}

// Função chamada quando o botão de ponto decimal é pressionado
void ponto_decimal_pressao(GtkWidget *widget, gpointer data) {
    adicionar_ponto_decimal();
}

// Função chamada quando o botão de limpar é pressionado
void limpar_pressao(GtkWidget *widget, gpointer data) {
    limpar_calculadora();
}

// Função para criar um botão
GtkWidget* criar_botao(const char *label, gpointer callback_data, GCallback callback_function) {
    GtkWidget *botao = gtk_button_new_with_label(label);
    g_signal_connect(botao, "clicked", callback_function, callback_data);
    return botao;
}

// Função para criar a interface gráfica da calculadora
void criar_calculadora(GtkWidget *janela) {
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_container_add(GTK_CONTAINER(j
