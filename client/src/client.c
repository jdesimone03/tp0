#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char *ip;
	char *puerto;
	char *valor;
	int config_ok = 1;

	t_log *logger;
	t_config *config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	if (config == NULL)
	{
		log_error(logger, "No existe el archivo de configuracion.");
		exit(-1);
	}

	// Usando el config creado previamente, leemos los valores del config y los
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	if (config_has_property(config, "IP"))
	{

		ip = config_get_string_value(config, "IP");
	}
	else
	{

		log_error(logger, "No encontre el valor 'IP' en la config.");

		config_ok = 0;
	}

	if (config_has_property(config, "PUERTO"))
	{

		puerto = config_get_string_value(config, "PUERTO");
	}
	else
	{

		log_error(logger, "No encontre el valor 'PUERTO' en la config.");

		config_ok = 0;
	}
	if (config_has_property(config, "CLAVE"))
	{

		valor = config_get_string_value(config, "CLAVE");
	}
	else
	{

		log_error(logger, "No encontre el valor 'CLAVE' en la config.");

		config_ok = 0;
	}

	if (!config_ok)
	{
		log_error(logger, "Error al cargar la configuracion! Revise bien el archivo e intente de nuevo.");
		exit(-1);
	}

	// Loggeamos el valor de config
	log_info(logger, "IP: %s, PUERTO: %s, VALOR: %s", ip, puerto, valor);

	// Destruimos el config y el log
	config_destroy(config);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	if(conexion == -1){
		log_error(logger, "Error al crear la conexion.");
		exit(-1);
	}
	log_info(logger, "Conexión creada");

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	log_info(logger, "Mensaje enviado");

	// Armamos y enviamos el paquete
	paquete(conexion);
	liberar_conexion(conexion);

	log_destroy(logger);
	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log *iniciar_logger(void)
{
	t_log *nuevo_logger = log_create("tp0.log", "Info", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config *iniciar_config(void)
{
	t_config *nuevo_config = config_create("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log *logger)
{
	char *leido;
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while (strcmp(leido, "") > 0)
	{
		log_info(logger, leido);
		free(leido);
		leido = readline("> ");
	}

	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char *leido;
	t_paquete *paquete;

	// Leemos y esta vez agregamos las lineas al paquete

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
