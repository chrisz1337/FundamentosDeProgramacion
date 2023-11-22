#include <iostream>
#include <vector>
#include <conio.h> // Biblioteca para el uso de getch() - password encriptada
#include<string>    
#include <windows.h> // Biblioteca para el uso de funciones específicas de Windows, como SetConsoleTextAttribute que se utiliza para cambiar el color del texto en la consola.
#include <limits>    // Biblioteca para el uso de características especiales de datos, como obtener el valor máximo o mínimo de un tipo de dato.
#include <iomanip>  // Biblioteca para el uso de manipuladores de formato, como setw, que se utiliza para establecer el ancho del campo al imprimir en la consola.
#include <cstdlib>  // Biblioteca que contiene funciones generales, incluida la función para salir del programa (system.exit).
#include <ctime>    // Biblioteca para el uso de funciones relacionadas con la fecha y hora (como la función time).
#include <sstream>  // Biblioteca para el uso de flujos de cadena de caracteres, que se utiliza para convertir entre cadenas y otros tipos de datos. - 
//Cuando trabajas con datos de diferentes tipos y necesitas construir una cadena de caracteres que combine estos datos en una oración o mensaje.

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Modificar color del texto

//ESTRUCTURAS
struct Usuario
{
    int codUsu;
    string nomUsu;
    string pasUsu;
    int tipUsu;
};

struct Vendedor
{
    int		codVendedor;
    string	nomVendedor;
    string  apeVendedor;
    int     dniVendedor;
};

struct Cliente
{
    int		codCliente;
    string	nomCliente;
    string  apeCliente;
    int     dniCliente;
};

struct Categoria
{
    int     codCategoria;
    string	nomCategoria;
};

struct Producto
{
    int		codProducto;
    string	nomProducto;
    float	preProducto;
    int		stkProducto;
    const Categoria* ptrCategoria;
};

struct Venta
{
    string fecha;
    float total;
};

//VECTORES
vector<Usuario>vecUsuario;
vector<Vendedor>vecVendedor;
vector<Producto>vecProducto;
vector<Categoria>vecCategoria;
vector<Cliente>vecCliente;
vector<Venta> vecVenta;

//USUARIO
void add();
void validarUsuario();

//ADMIN
void menuOpcionesAdmin();
void registrarVendedor();
void menuOpcionesVendedor();
void registrarVendedor();
void addVendedor();
void listadoVendedor();
int	 getCorrelativoV();
void buscarVendedorPorCodigo();
void removeVendedor();
void modifyVendedor();
int	 obtenerPosArregloV(int);

void mostrarListaVentas();
void agregarVentaALista(const string& fecha, float total);

//VENDEDOR
void listaPC();
void seleccionarProductos();
float seleccionarIGV();
void generarVenta();
void anularVenta();
string obtenerFechaSistema();

//CLIENTE
void registrarCliente();
void addCliente();
void listadoCliente();
int	 getCorrelativoC();
void buscarClientePorCodigo();
void removeCliente();
void modifyCliente();
int	 obtenerPosArregloC(int);

//PRODUCTO
void registrarProducto();
void addProducto();
int getCorrelativoP();
void listadoProducto();
void buscarProductoPorCodigo();
void removeProducto();
void modifyProducto();
int obtenerPosArregloP(int);

//DATOS FIJOS
void cargarDatosFijos();

//CATEGORIA
void registarCategoria();
void addCategoria();
void addCategoria();
int getCorrelativoCA();
void listadoCategoria();
void buscarCategoriaPorCodigo();
void removeCategoria();
void modifyCategoria();
int obtenerPosArregloCA(int);

int main()
{
    cargarDatosFijos();
    add();
    validarUsuario();
}

void add()
{
    //Carga datos fijos 
    Usuario usuario;
    usuario.codUsu = 1;
    usuario.nomUsu = "admin";
    usuario.pasUsu = "admin";
    usuario.tipUsu = 1; //1. Admin - 2. Vendedor
    vecUsuario.push_back(usuario);

    vecUsuario.push_back({ 2, "vendedor", "vendedor",2 });
}
void validarUsuario()
{
    string user, password;
    bool flag = false;
    int pos;

    do
    {
    SetConsoleTextAttribute(hConsole, 2);
    cout << "Acceso al sistema\n";
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Ingrese su usuario: ";
    cin >> user;
    cout << "Ingrese su contrasena: ";
    char caracter;
    password = "";
    while ((caracter = _getch()) != 13) // 13 es el código ASCII de la tecla Enter, significa que la entrada de la contraseña continuará hasta que el usuario presione Enter.
    {
        if (caracter == 8) // 8 es el código ASCII de la tecla Backspace, Se verifica si el carácter ingresado es la tecla Backspace (cuyo código ASCII es 8).
                     // Si es así, se verifica que la longitud de la contraseña sea mayor que 0 para evitar errores al intentar borrar un carácter cuando la contraseña está vacía.
        {
            if (password.size() > 0)
            {
                cout << "\b \b"; // Si se presiona Backspace, se retrocede el cursor en la consola (\b \b) para simular la eliminación del último carácter ingresado.
                password.pop_back(); // Se elimina el último carácter de la cadena password utilizando pop_back().
            }
        }
        else
        {
            cout << '*'; // Si el carácter ingresado no es Backspace, se imprime un asterisco (*) en la pantalla para ocultar el carácter.
            password.push_back(caracter); // El carácter ingresado se agrega al final de la cadena password utilizando push_back().
        }
    }
    cout << endl;

    for (int i = 0; i < vecUsuario.size(); i++)
    {
        if (user == vecUsuario[i].nomUsu && 
            password == vecUsuario[i].pasUsu)
        {
            flag = true;
            pos = i;
            break;
        }
    }

    if (!flag) // se evalua como falso.
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "Acceso denegado. Por favor, ingrese datos validos.\n";
        SetConsoleTextAttribute(hConsole, 7);
        system("pause");
        system("cls");
    }

    } while (!flag); // hasta que sea vuelva true.

    SetConsoleTextAttribute(hConsole, 2);
    cout << "Acceso correcto\n";
    SetConsoleTextAttribute(hConsole, 7);
    system("pause");
    system("cls");

    switch (vecUsuario[pos].tipUsu)
    {
    case 1:
        system("cls");
        menuOpcionesAdmin();
        break;
    case 2:
        system("cls");
        menuOpcionesVendedor();
        break;
    }
}

void menuOpcionesAdmin()
{
    int opcion;
    do {


        SetConsoleTextAttribute(hConsole, 1);
        cout << "\t\t\t\tM E N U  D E  O P C I O N E S  A D M I N\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Registrar vendedor     [1]\n";
        cout << "Registrar producto     [2]\n";
        cout << "Registrar categoria    [3]\n";
        cout << "Listado de ventas      [4]\n";
        cout << "Salir                  [5]\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarVendedor();
            break;
        case 2:
            registrarProducto();
            break;
        case 3:
            registarCategoria();
            break;
        case 4:
            mostrarListaVentas();
            break;
        case 5:
            break;
        default:
            SetConsoleTextAttribute(hConsole, 4);
            cout << "Ingrese una opcion correcta [1-5]\n";
            SetConsoleTextAttribute(hConsole, 7);
        }
    } while (opcion != 5);
}

void menuOpcionesVendedor()
{
    int opcion;
    do {
        

        SetConsoleTextAttribute(hConsole, 1);
        cout << "\t\t\t\tM E N U  D E  O P C I O N E S  V E N D E D O R\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Registrar cliente           [1]\n";
        cout << "Lista de productos          [2]\n";
        cout << "Generar venta               [3]\n";
        cout << "Anular venta                [4]\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarCliente();
            break;
        case 2:
            listaPC();
            break;
        case 3:
            generarVenta();
            break;
        case 4:
            anularVenta();
            break;
        default:
            cout << "Ingrese una opcion correcta [1-4]\n";
        }
    } while (opcion != 4);
}


void registrarCliente()
{
    int opcion;
    do
    {
        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 1);
        cout << "\t\t\t\tM E N U  D E  O P C I O N E S\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Agregar clientes_________________[1]\n";
        cout << "Buscar clientes__________________[2]\n";
        cout << "Eliminar clientes________________[3]\n";
        cout << "Modificar clientes_______________[4]\n";
        cout << "Listar clientes__________________[5]\n";
        cout << "Salir____________________________[6]\n";
        cout << "Ingrese una opcion:";
        cin >> opcion;
        switch (opcion)
        {
        case 1:system("cls"); addCliente(); break;
        case 2:system("cls"); buscarClientePorCodigo(); break;
        case 3:	system("cls");
            removeCliente();
            break;
        case 4:	system("cls");
            modifyCliente();
            break;
        case 5:	system("cls");
            listadoCliente();
            break;
        case 6:system("cls"); break;
        default:system("cls");
            SetConsoleTextAttribute(hConsole, 4);
            cout << "Ingrese una opcion correcta[1-6]\n";
            SetConsoleTextAttribute(hConsole, 7);
        }
    } while (opcion != 6);
}

void addCliente()
{
    string rpta;
    do
    {
        Cliente cliente;

        cout << "Codigo:" << getCorrelativoC() << endl;
        cliente.codCliente = getCorrelativoC();
        cin.ignore();//limpiar el buffer
        cout << "Nombre:";
        getline(cin, cliente.nomCliente);
        cout << "Apellido:";
        getline(cin, cliente.apeCliente);
        cout << "DNI:";
        do {
            cin >> cliente.dniCliente;

            if (cin.fail()) {
                cin.clear(); // Limpiar el indicador de error
                cin.ignore(INT_MAX, '\n'); // Descartar la entrada incorrecta limpiando
                cout << "Ingrese un número válido para el DNI: ";
            }
            else if (to_string(cliente.dniCliente).length() != 8) {
                // Si el DNI no tiene 8 dígitos
                SetConsoleTextAttribute(hConsole, 4);
                cout << "El DNI debe tener exactamente 8 digitos. \nIngrese nuevamente: ";
                SetConsoleTextAttribute(hConsole, 7);
            }

        } while (to_string(cliente.dniCliente).length() != 8);

        vecCliente.push_back(cliente);
        SetConsoleTextAttribute(hConsole, 2);
        cout << "Deseas continuar registrando clientes....(S/N): \n";
        SetConsoleTextAttribute(hConsole, 7);
        cin >> rpta;
    } while (rpta == "S" || rpta == "s");
}

int getCorrelativoC()
{
    if (vecCliente.size() == 0)
    {
        return 1;
    }
    else
    {
        return vecCliente[vecCliente.size() - 1].codCliente + 1;
    }
}

void listadoCliente()
{
        cout << "Registro de clientes\n";
        for (int i = 0; i < vecCliente.size(); i++)
        {
            cout << "________________________________\n";
            cout << "Codigo:" << vecCliente[i].codCliente << endl;
            cout << "Nombre:" << vecCliente[i].nomCliente << endl;
            cout << "Apellido: " << vecCliente[i].apeCliente << endl;
            cout << "DNI:" << vecCliente[i].dniCliente << endl;
            cout << "________________________________\n";
        }
}

void buscarClientePorCodigo()
{
        int codigo;
        bool flag = false;
        int pos;
        cout << "Ingrese codigo a buscar: ";
        cin >> codigo;
        for (int i = 0; i < vecCliente.size(); i++)
        {
            if (codigo == vecCliente[i].codCliente)
            {
                pos = i;
                flag = true;
            }
        }
        if (flag == true)
        {
            system("cls");
            cout << "Registro encontrado (" << pos << ")\n";
            cout << "-----------------------------------\n";
            cout << "Codigo: " << vecCliente[pos].codCliente << endl;
            cout << "Nombre: " << vecCliente[pos].nomCliente << endl;
            cout << "Apellido: " << vecCliente[pos].apeCliente << endl;
            cout << "DNI: " << vecCliente[pos].dniCliente << endl;
            
        }
        else
        {
            cout << "No se ha encontrado ningun registro\n";
            
        }
}
void removeCliente()
{
    int codigo;
    bool flag = false;
    cout << "Ingrese codigo del cliente a eliminar:";
    cin >> codigo;
    for (int i = 0; i < vecCliente.size(); i++)
    {
        if (codigo == vecCliente[i].codCliente)
        {
            vecCliente.erase(vecCliente.begin() + i);
            cout << "Registro del cliente eliminado.\n";
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
}
void modifyCliente()
{
    int codigo,
        posicion,
        opcion;
    string _nombre,
           _apellido;
    int    _dni;
    cout << "Ingrese un codigo a modificar: ";
    cin >> codigo;
    posicion = obtenerPosArregloC(codigo);
    if (posicion == -1)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << "-------------------\n";
        cout << "Registro encontrado\n";
        cout << "-------------------\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Codigo:" << vecCliente[posicion].codCliente << endl;
        cout << "Nombre:" << vecCliente[posicion].nomCliente << endl;
        cout << "Apellido:" << vecCliente[posicion].apeCliente << endl;
        cout << "DNI:" << vecCliente[posicion].dniCliente << endl;

        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\t\t\t\tMINI MENU\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Nombre\t\t[1]\n";
        cout << "DNI\t\t[2]\n";
        cout << "Salir\t\t[3]\n";
        cout << "Seleccionar una opcion[1-3]:";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1: cout << "Cambiar nombre:";
            getline(cin, _nombre);
            vecCliente[posicion].nomCliente = _nombre;
            system("pause");
            system("cls");
            break;
        case 2: cout << "Cambiar apellido:";
            getline(cin, _apellido);
            vecCliente[posicion].apeCliente = _apellido;
            system("pause");
            system("cls");
            break;
        case 3: cout << "Cambiar DNI: ";
            do {
                cin >> _dni;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Ingrese un número válido para el DNI: ";
                }
                else if (to_string(_dni).length() != 8) {
                    cout << "El DNI debe tener exactamente 8 digitos. \nIngrese nuevamente: ";
                }

            } while (to_string(_dni).length() != 8);

            vecCliente[posicion].dniCliente = _dni;
            break;
        case 4:break;
        default:cout << "Ingrese una opcion correcta[1-4]\n";
        }
    }
}
int	 obtenerPosArregloC(int cod)
{
    for (int i = 0; i < vecCliente.size(); i++)
    {
        if (cod == vecCliente[i].codCliente)
        {
            return i;
        }
    }
    return -1;
}

void registrarProducto()
{
    int opcion;
    do
    {
        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\t\t\t\tM E N U  D E  O P C I O N E S\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Agregar producto_________________[1]\n";
        cout << "Buscar producto__________________[2]\n";
        cout << "Eliminar producto________________[3]\n";
        cout << "Modificar producto_______________[4]\n";
        cout << "Lista de productos_______________[5]\n";
        cout << "Salir____________________________[6]\n";
        cout << "Ingrese una opcion:";
        cin >> opcion;
        switch (opcion)
        {
        case 1:system("cls"); addProducto(); break;
        case 2:system("cls"); buscarProductoPorCodigo(); break;
        case 3:	system("cls");
            removeProducto();
            break;
        case 4:	system("cls");
            modifyProducto();
            break;
        case 5:	system("cls");
            listadoProducto();
            break;
        case 6:system("cls"); break;
        default:system("cls");
            cout << "Ingrese una opcion correcta[1-6]\n";
        }
    } while (opcion != 6);
}

void addProducto()
{
    string rpta;
    do
    {
        Producto producto;

        cout << "Codigo: " << getCorrelativoP() << endl;
        producto.codProducto = getCorrelativoP();
        cin.ignore();
        cout << "Nombre: ";
        getline(cin, producto.nomProducto);
        cout << "Precio: "; cin >> producto.preProducto;
        cout << "Stock: "; cin >> producto.stkProducto;

        vecProducto.push_back(producto);

        cout << "Deseas continuar registrando productos....(S/N):";
        cin >> rpta;

    } while (rpta == "S" || rpta == "s");
}

int getCorrelativoP()
{
    if (vecProducto.size() == 0)
    {
        return 1;
    }
    else
    {
        return vecProducto[vecProducto.size() - 1].codProducto + 1;
    }
}

void listadoProducto()
{
    cout << "Registro de clientes\n";
    for (int i = 0; i < vecProducto.size(); i++)
    {
        cout << "________________________________\n";
        cout << "Codigo: " << vecProducto[i].codProducto << endl;
        cout << "Nombre: " << vecProducto[i].nomProducto << endl;
        cout << "Precio: " << vecProducto[i].preProducto << endl;
        cout << "Stock:  " << vecProducto[i].stkProducto << endl;
        cout << "________________________________\n";
    }
}

void buscarProductoPorCodigo()
{
    int codigo;
    bool flag = false;
    int pos;
    cout << "Ingrese codigo a buscar: ";
    cin >> codigo;
    for (int i = 0; i < vecProducto.size(); i++)
    {
        if (codigo == vecProducto[i].codProducto)
        {
            pos = i;
            flag = true;
        }
    }
    if (flag == true)
    {
        system("cls");
        cout << "Registro encontrado (" << pos << ")\n";
        cout << "-----------------------------------\n";
        cout << "Codigo: " << vecProducto[pos].codProducto << endl;
        cout << "Nombre: " << vecProducto[pos].nomProducto << endl;
        cout << "Precio: " << vecProducto[pos].preProducto << endl;
        cout << "Stock:  " << vecProducto[pos].stkProducto << endl;

    }
    else
    {
        cout << "No se ha encontrado ningun registro\n";

    }
}
void removeProducto()
{
    int codigo;
    bool flag = false;
    cout << "Ingrese codigo del producto a eliminar:";
    cin >> codigo;
    for (int i = 0; i < vecProducto.size(); i++)
    {
        if (codigo == vecProducto[i].codProducto)
        {
            vecProducto.erase(vecProducto.begin() + i);
            cout << "Registro del producto eliminado.\n";
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
}
void modifyProducto()
{
    int codigo,
        posicion,
        opcion;
    string _nombre;
    float  _precio;
    int    _stock;
    cout << "Ingrese un codigo a modificar: ";
    cin >> codigo;
    posicion = obtenerPosArregloP(codigo);
    if (posicion == -1)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << "-------------------\n";
        cout << "Registro encontrado\n";
        cout << "-------------------\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Codigo:" << vecProducto[posicion].codProducto << endl;
        cout << "Nombre:" << vecProducto[posicion].nomProducto << endl;
        cout << "Precio:" << vecProducto[posicion].preProducto << endl;
        cout << "Stock:" << vecProducto[posicion].stkProducto << endl;

        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 5);
        cout << "\t\t\t\tMINI MENU\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Nombre\t\t[1]\n";
        cout << "Precio\t\t[2]\n";
        cout << "Stock\t\t[3]\n";
        cout << "Salir\t\t[4]\n";
        cout << "Seleccionar una opcion[1-4]:";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1: cout << "Cambiar nombre: ";
            getline(cin, _nombre);
            vecProducto[posicion].nomProducto = _nombre;
            break;
        case 2: cout << "Cambiar precio: ";
            cin >> _precio;
            vecProducto[posicion].preProducto = _precio;
            break;
        case 3: cout << "Cambiar stock: ";
            cin >> _stock;
            vecProducto[posicion].stkProducto = _stock;
            break;
        case 4:break;
        default:cout << "Ingrese una opcion correcta[1-4]\n";
        }
    }
}
int	 obtenerPosArregloP(int cod)
{
    for (int i = 0; i < vecProducto.size(); i++)
    {
        if (cod == vecProducto[i].codProducto)
        {
            return i;
        }
    }
    return -1;
}

void registrarVendedor()
{
    int opcion;
    do
    {
        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\t\t\t\tM E N U  D E  O P C I O N E S\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Agregar vendedor_________________[1]\n";
        cout << "Buscar vendedor__________________[2]\n";
        cout << "Eliminar vendedor________________[3]\n";
        cout << "Modificar vendedor_______________[4]\n";
        cout << "Listar vendedor__________________[5]\n";
        cout << "Salir____________________________[6]\n";
        cout << "Ingrese una opcion:";
        cin >> opcion;
        switch (opcion)
        {
        case 1:system("cls"); addVendedor(); break;
        case 2:system("cls"); buscarVendedorPorCodigo(); break;
        case 3:	system("cls");
            removeVendedor();
            break;
        case 4:	system("cls");
            modifyVendedor();
            break;
        case 5:	system("cls");
            listadoVendedor();
            break;
        case 6:system("cls"); break;
        default:system("cls");
            cout << "Ingrese una opcion correcta[1-6]\n";
        }
    } while (opcion != 6);
}

void addVendedor()
{
    string rpta;
    do
    {
        Vendedor vendedor;

        cout << "Codigo:" << getCorrelativoV() << endl;
        vendedor.codVendedor = getCorrelativoV();
        cin.ignore();//limpiar el buffer
        cout << "Nombre:";
        getline(cin, vendedor.nomVendedor);
        cout << "Apellido:";
        getline(cin, vendedor.apeVendedor);
        cout << "DNI:";
        do {
            cin >> vendedor.dniVendedor;

            if (cin.fail()) {
                cin.clear(); // Limpiar el indicador de error
                cin.ignore(INT_MAX, '\n'); // Descartar la entrada incorrecta limpiando
                cout << "Ingrese un número válido para el DNI: ";
            }
            else if (to_string(vendedor.dniVendedor).length() != 8) {
                // Si el DNI no tiene 8 dígitos
                cout << "El DNI debe tener exactamente 8 digitos. \nIngrese nuevamente: ";
            }

        } while (to_string(vendedor.dniVendedor).length() != 8);

        vecVendedor.push_back(vendedor);

        cout << "Deseas continuar registrando vendedores....(S/N): ";
        cin >> rpta;
    } while (rpta == "S" || rpta == "s");
}

int getCorrelativoV()
{
    if (vecVendedor.size() == 0)
    {
        return 1;
    }
    else
    {
        return vecVendedor[vecVendedor.size() - 1].codVendedor + 1;
    }
}

void listadoVendedor()
{
    cout << "Registro de vendedores\n";
    for (int i = 0; i < vecVendedor.size(); i++)
    {
        cout << "________________________________\n";
        cout << "Codigo:" << vecVendedor[i].codVendedor << endl;
        cout << "Nombre:" << vecVendedor[i].nomVendedor << endl;
        cout << "Apellido: " << vecVendedor[i].apeVendedor << endl;
        cout << "DNI:" << vecVendedor[i].dniVendedor << endl;
        cout << "________________________________\n";
    }
}

void buscarVendedorPorCodigo()
{
    int codigo;
    bool flag = false;
    int pos;
    cout << "Ingrese codigo a buscar: ";
    cin >> codigo;
    for (int i = 0; i < vecVendedor.size(); i++)
    {
        if (codigo == vecVendedor[i].codVendedor)
        {
            pos = i;
            flag = true;
        }
    }
    if (flag == true)
    {
        system("cls");
        cout << "Registro encontrado (" << pos << ")\n";
        cout << "-----------------------------------\n";
        cout << "Codigo: " << vecVendedor[pos].codVendedor << endl;
        cout << "Nombre: " << vecVendedor[pos].nomVendedor << endl;
        cout << "Apellido: " << vecVendedor[pos].apeVendedor << endl;
        cout << "DNI: " << vecVendedor[pos].dniVendedor << endl;

    }
    else
    {
        cout << "No se ha encontrado ningun registro\n";

    }
}
void removeVendedor()
{
    int codigo;
    bool flag = false;
    cout << "Ingrese codigo del vendedor a eliminar:";
    cin >> codigo;
    for (int i = 0; i < vecVendedor.size(); i++)
    {
        if (codigo == vecVendedor[i].codVendedor)
        {
            vecVendedor.erase(vecVendedor.begin() + i);
            cout << "Registro del vendedor eliminado.\n";
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
}
void modifyVendedor()
{
    int codigo,
        posicion,
        opcion;
    string _nombre,
        _apellido;
    int    _dni;
    cout << "Ingrese un codigo a modificar: ";
    cin >> codigo;
    posicion = obtenerPosArregloV(codigo);
    if (posicion == -1)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << "-------------------\n";
        cout << "Registro encontrado\n";
        cout << "-------------------\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Codigo:" << vecVendedor[posicion].codVendedor << endl;
        cout << "Nombre:" << vecVendedor[posicion].nomVendedor << endl;
        cout << "Apellido:" << vecVendedor[posicion].apeVendedor << endl;
        cout << "DNI:" << vecVendedor[posicion].dniVendedor << endl;

        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\t\t\t\tMINI MENU\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Nombre\t\t[1]\n";
        cout << "Apellido\t\t[2]\n";
        cout << "DNI\t\t[3]\n";
        cout << "Salir\t\t[4]\n";
        cout << "Seleccionar una opcion[1-4]:";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1: cout << "Cambiar nombre:";
            getline(cin, _nombre);
            vecVendedor[posicion].nomVendedor = _nombre;
            system("pause");
            system("cls");
            break;
        case 2: cout << "Cambiar apellido:";
            getline(cin, _apellido);
            vecVendedor[posicion].apeVendedor = _apellido;
            system("pause");
            system("cls");
            break;
        case 3: cout << "Cambiar DNI: ";
            do {
                cin >> _dni;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Ingrese un número válido para el DNI: ";
                }
                else if (to_string(_dni).length() != 8) {
                    cout << "El DNI debe tener exactamente 8 digitos. \nIngrese nuevamente: ";
                }

            } while (to_string(_dni).length() != 8);

            vecVendedor[posicion].dniVendedor = _dni;
            break;
        case 4:break;
        default:cout << "Ingrese una opcion correcta[1-4]\n";
        }
    }
}
int	 obtenerPosArregloV(int cod)
{
    for (int i = 0; i < vecVendedor.size(); i++)
    {
        if (cod == vecVendedor[i].codVendedor)
        {
            return i;
        }
    }
    return -1;
}

void registarCategoria()
{
    int opcion;
    do
    {
        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\t\t\t\tM E N U  D E  O P C I O N E S\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Agregar categoria_________________[1]\n";
        cout << "Buscar categoria__________________[2]\n";
        cout << "Eliminar categoria________________[3]\n";
        cout << "Modificar categoria_______________[4]\n";
        cout << "Listar categoria__________________[5]\n";
        cout << "Salir_____________________________[6]\n";
        cout << "Ingrese una opcion:";
        cin >> opcion;
        switch (opcion)
        {
        case 1:system("cls"); addCategoria(); break;
        case 2:system("cls"); buscarCategoriaPorCodigo(); break;
        case 3:	system("cls");
            removeCategoria();
            break;
        case 4:	system("cls");
            modifyCategoria();
            break;
        case 5:	system("cls");
            listadoCategoria();
            break;
        case 6:system("cls"); break;
        default:system("cls");
            cout << "Ingrese una opcion correcta[1-6]\n";
        }
    } while (opcion != 6);
}

void addCategoria()
{
    string rpta;
    do
    {
        Categoria categoria;

        cout << "Codigo:" << getCorrelativoCA() << endl;
        categoria.codCategoria = getCorrelativoCA();
        cin.ignore();//limpiar el buffer
        cout << "Nombre:";
        getline(cin, categoria.nomCategoria);

        vecCategoria.push_back(categoria);

        cout << "Deseas continuar registrando categorias....(S/N): ";
        cin >> rpta;
    } while (rpta == "S" || rpta == "s");
}

int getCorrelativoCA()
{
    if (vecCategoria.size() == 0)
    {
        return 1;
    }
    else
    {
        return vecCategoria[vecCategoria.size() - 1].codCategoria + 1;
    }
}

void listadoCategoria()
{
   
    cout << "Registro de categorias\n";
    for (int i = 0; i < vecCategoria.size(); i++)
    {
        cout << "________________________________\n";
        cout << "Codigo:" << vecCategoria[i].codCategoria << endl;
        cout << "Nombre:" << vecCategoria[i].nomCategoria << endl;
        cout << "________________________________\n";
    }
}

void buscarCategoriaPorCodigo()
{
    int codigo;
    bool flag = false;
    int pos;
    cout << "Ingrese codigo a buscar: ";
    cin >> codigo;
    for (int i = 0; i < vecCategoria.size(); i++)
    {
        if (codigo == vecCategoria[i].codCategoria)
        {
            pos = i;
            flag = true;
        }
    }
    if (flag == true)
    {
        system("cls");
        cout << "Registro encontrado (" << pos << ")\n";
        cout << "-----------------------------------\n";
        cout << "Codigo: " << vecCategoria[pos].codCategoria << endl;
        cout << "Nombre: " << vecCategoria[pos].nomCategoria << endl;

    }
    else
    {
        cout << "No se ha encontrado ningun registro\n";

    }
}
void removeCategoria()
{
    int codigo;
    bool flag = false;
    cout << "Ingrese codigo de la categoria a eliminar:";
    cin >> codigo;
    for (int i = 0; i < vecCategoria.size(); i++)
    {
        if (codigo == vecCategoria[i].codCategoria)
        {
            vecCategoria.erase(vecCategoria.begin() + i);
            cout << "Registro de la categoria eliminada.\n";
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
}
void modifyCategoria()
{
    int codigo,
        posicion,
        opcion;
    string _nombre;

    cout << "Ingrese un codigo a modificar: ";
    cin >> codigo;
    posicion = obtenerPosArregloCA(codigo);
    if (posicion == -1)
    {
        cout << "ERROR: Codigo inexistente\n";
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << "-------------------\n";
        cout << "Registro encontrado\n";
        cout << "-------------------\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Codigo:" << vecCategoria[posicion].codCategoria << endl;
        cout << "Nombre:" << vecCategoria[posicion].nomCategoria << endl;

        system("pause");
        system("cls");
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\t\t\t\tMINI MENU\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Nombre\t\t[1]\n";
        cout << "Salir\t\t[2]\n";
        cout << "Seleccionar una opcion[1-2]:";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1: cout << "Cambiar nombre:";
            getline(cin, _nombre);
            vecCategoria[posicion].nomCategoria = _nombre;
            system("pause");
            system("cls");
            break;
        case 2:break;
        default:cout << "Ingrese una opcion correcta[1-2]\n";
        }
    }
}
int	 obtenerPosArregloCA(int cod)
{
    for (int i = 0; i < vecCategoria.size(); i++)
    {
        if (cod == vecCategoria[i].codCategoria)
        {
            return i;
        }
    }
    return -1;
}


void listaPC()
{
    system("cls");
    cout << setw(10) << "Codigo" << setw(20) << "Producto" << setw(10) << "Precio" << setw(10) << "Stock" << setw(20) << "Categoria" << endl;

    for (const Producto& producto : vecProducto)
    {
        cout << setw(10) << producto.codProducto
            << setw(20) << producto.nomProducto
            << setw(10) << fixed << setprecision(2) << producto.preProducto
            << setw(10) << producto.stkProducto
            << setw(20) << producto.ptrCategoria->nomCategoria
            << endl;
    }

    system("pause");
    system("cls");
}

void seleccionarProductos()
{
    int opcionProducto;
    string rpta;
    vector<int> productosSeleccionados;

    do
    {
        system("cls");
        cout << "Seleccione un producto ingresando su código: ";
        cin >> opcionProducto;

        if (opcionProducto >= 0 && opcionProducto < vecProducto.size() && (opcionProducto == 0 || !vecProducto[opcionProducto].nomProducto.empty()))
        {
            productosSeleccionados.push_back(opcionProducto);
            SetConsoleTextAttribute(hConsole, 2);
            cout << "Producto seleccionado: " << vecProducto[opcionProducto].nomProducto << endl;
            SetConsoleTextAttribute(hConsole, 7);
        }
        else if (opcionProducto != 0)
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "Código de producto no válido. Por favor, intente de nuevo.\n";
            SetConsoleTextAttribute(hConsole, 7);
        }

        cout << "Deseas continuar seleccionando productos (S/N): ";
        cin >> rpta;

    } while (rpta == "S" || rpta == "s");

    system("cls");
    // Mostrar listado de productos seleccionados
    SetConsoleTextAttribute(hConsole, 1);
    cout << "Listado de productos seleccionados:\n";
    SetConsoleTextAttribute(hConsole, 7);
    for (int codigo : productosSeleccionados)
    {
        cout << "Codigo: " << codigo << " - Producto: " << vecProducto[codigo].nomProducto << endl;
    }

    system("pause");
    system("cls");
}

void cargarDatosFijos()
{
    // Datos fijos de categorías
    vecCategoria.push_back({ 0, "Electronicos" });
    vecCategoria.push_back({ 1, "Ropa" });
    vecCategoria.push_back({ 2, "Hogar" });
    vecCategoria.push_back({ 3, "Deportes" });
    vecCategoria.push_back({ 4, "Libros" });

    // Ddatos fijos de productos
    vecProducto.push_back({ 0, "Smartphone", 499.99, 50, &vecCategoria[0] });
    vecProducto.push_back({ 1, "Camiseta", 19.99, 100, &vecCategoria[1] });
    vecProducto.push_back({ 2, "Sarten", 29.99, 30, &vecCategoria[2] });
    vecProducto.push_back({ 3, "Balon de futbol", 14.99, 20, &vecCategoria[3] });
    vecProducto.push_back({ 4, "Novela", 9.99, 80, &vecCategoria[4] });

    // Datos fijos para Vendedores
    vecVendedor.push_back({ 0, "Juan", "Perez", 12345678 });
    vecVendedor.push_back({ 1, "Ana", "Gomez", 23456789 });
    vecVendedor.push_back({ 2, "Carlos", "Lopez", 34567890 });
    vecVendedor.push_back({ 3, "Laura", "Martinez", 45678901 });
    vecVendedor.push_back({ 4, "Javier", "Fernandez", 56789012 });

    // Datos fijos para Clientes
    vecCliente.push_back({ 0, "Maria", "Rodriguez", 98765432 });
    vecCliente.push_back({ 1, "Pedro", "Garcia", 87654321 });
    vecCliente.push_back({ 2, "Luisa", "Fernandez", 76543210 });
    vecCliente.push_back({ 3, "Elena", "Gonzalez", 65432109 });
    vecCliente.push_back({ 4, "Miguel", "Lopez", 54321098 });

    // Datos fijos para Ventas
    vecVenta.push_back({ "21-11-2023", 35.0 });
    vecVenta.push_back({ "21-11-2023", 45.7 });
    vecVenta.push_back({ "21-11-2023", 16.5 });
    vecVenta.push_back({ "21-11-2023", 17.8 });
    vecVenta.push_back({ "21-11-2023", 24.2 });
}

float seleccionarIGV()
{
    float porcentajeIGV;

    system("cls");
    cout << "Ingrese el porcentaje de IGV: ";
    cin >> porcentajeIGV;

    // Validación del porcentaje de IGV
    if (porcentajeIGV >= 0)
    {
        SetConsoleTextAttribute(hConsole, 2);
        cout << "IGV ingresado: " << porcentajeIGV << "%" << endl;
        SetConsoleTextAttribute(hConsole, 7);

        system("pause");
        system("cls");
        return porcentajeIGV;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "Porcentaje de IGV no válido. El valor ingresado debe ser mayor o igual a cero." << endl;
        SetConsoleTextAttribute(hConsole, 7);
        system("pause");
        system("cls");
    }
}

string obtenerFechaSistema()
{
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    // Formato de fecha: dd-mm-yyyy
    stringstream ss;
    ss << setw(2) << setfill('0') << now.tm_mday << '-' << setw(2) << setfill('0') << now.tm_mon + 1 << '-' << now.tm_year + 1900;
    return ss.str();
}

void generarVenta()
{
    float igv;

    seleccionarProductos();
    igv = seleccionarIGV();

    // Calcular el total sumando los precios de los productos
    float total = 0;
    for (const Producto& producto : vecProducto)
    {
        total += producto.preProducto;
    }

    // Agregar el IGV al total
    total += total * (igv / 100);

    // Obtener la fecha del sistema
    string fechaSistema = obtenerFechaSistema();

    // Imprimir la fecha del sistema
    cout << "Fecha de la venta: " << fechaSistema << endl;

    // Imprimir el total, incluyendo el IGV
    SetConsoleTextAttribute(hConsole, 2);
    cout << "Total de la venta (incluyendo IGV): S/. " << total << endl;
    SetConsoleTextAttribute(hConsole, 7);
    
    system("pause");
    system("cls");

    agregarVentaALista(fechaSistema, total);

}

void anularVenta()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 4);
    cout << "Se ha anulado la venta" << endl;
    SetConsoleTextAttribute(hConsole, 7);
    system("pause");
    exit(0);
}

// Función para agregar la venta a la lista
void agregarVentaALista(const string& fecha, float total)
{
    // Crear un objeto de la estructura Venta con la fecha y total
    Venta nuevaVenta = { fecha, total };

    // Agregar la nueva venta al vector global vecVenta
    vecVenta.push_back(nuevaVenta);
}

// Función para mostrar la lista de ventas
void mostrarListaVentas()
{
    system("cls");
    // Mostrar encabezado
    cout << setw(15) << "Fecha" << setw(15) << "Total" << endl;

    // Mostrar cada venta en la lista
    for (const Venta& venta : vecVenta)
    {
        cout << setw(15) << venta.fecha << setw(15) << venta.total << endl;
    }

    // Pausar y limpiar la pantalla
    system("pause");
    system("cls");
}