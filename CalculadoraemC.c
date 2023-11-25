#include <gtk/gtk.h>

// Variaveis Globais para a calculadora
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

// Função para realizar a operação selecionada
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

// Função chamada quando o botão de número é pressionado
void numero_pressao(GtkWidget *widget, gpointer data) {
    int n = GPOINTER_TO_INT(data);
    adicionar_numero(n);
}

// Função chamada quando o botão de operação é pressionado
void operacao_pressao(GtkWidget *widget, gpointer data) {
    char op = *(char*)data;
    num1 = num2;
    realizar_operacao(op);
}

// funçao de limpeza da calculadora
void limpar_calculadora() {
    gtk_label_set_text(GTK_LABEL(result_label), NULL);
}

// Função chamada quando o botão de ponto decimal é pressionado
void ponto_decimal_pressao(GtkWidget *widget, gpointer data) {
    adicionar_ponto_decimal();
}

// Função chamada quando o botão de limpar é pressionado
void limpar_pressao(GtkWidget *widget, gpointer data) {
    limpar_calculadora();
}

// Função para criar um botão com um rótulo e uma função de callback
GtkWidget* criar_botao(const gchar *label, GCallback callback, gpointer data) {
    GtkWidget *botao = gtk_button_new_with_label(label);
    g_signal_connect(botao, "clicado", callback, data);
    return botao;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    //Criação da janela inicial
    GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela), "calculadora");
    gtk_container_set_border_width(GTK_CONTAINER(janela), 10);
    g_signal_connect(janela, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //Criação do layout da calculadora
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_container_add(GTK_CONTAINER(janela), grid);

    // Criação dos labels para exibir os numeros
    result_label = gtk_label_new("0");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 0, 4, 1);

    // Criação dos botoes numericos e de operação
    gchar *button_labels[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", ".", "+", "-", "*", "/"};
    for (int i = 0; i < 16; i++) {
        GtkWidget *botao;
        if (i < 11) {
            botao = criar_botao(button_labels[i], G_CALLBACK(numero_pressao), GINT_TO_POINTER(i));
        } else {
            botao = criar_botao(button_labels[i], G_CALLBACK(operacao_pressao), &button_labels[i][0]);
        }
        gtk_grid_attach(GTK_GRID(grid), botao, i % 4, 2 + i / 4, 1, 1);
    }

    // Criação de botão de limpar
    GtkWidget *button_clear = criar_botao("C", NULL, G_CALLBACK(limpar_pressao));
    gtk_grid_attach(GTK_GRID(grid), button_clear, 0, 6, 2, 1);

    // Exibição da janela de inicio do loop principal do gdk
    gtk_widget_show_all(janela);
    gtk_main();
    return 0;
}
