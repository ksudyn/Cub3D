# cub3D (42 Project)

## Introducción

**cub3D** es un proyecto de la escuela 42 cuyo objetivo es el desarrollo de un **motor gráfico 3D en C** desde cero. Inspirado en el mítico *Wolfenstein 3D* (1992), el proyecto utiliza la técnica de **Raycasting** para renderizar una perspectiva tridimensional a partir de un mapa estrictamente bidimensional.

Este proyecto consolida conceptos avanzados de matemáticas geométricas (trigonometría, vectores), gestión de ventanas, renderizado de imágenes a bajo nivel y parsing estricto de archivos de configuración.

### Objetivos Técnicos Alcanzados:
- Implementación del algoritmo de **Raycasting** para proyección 3D.
- Uso eficiente de la librería gráfica **MiniLibX** (X11/Linux) para el manejo de ventanas y buffers de imagen.
- Parsing y validación robusta de mapas dinámicos (`.cub`).
- Gestión matemática de vectores para el movimiento, rotación y colisiones del jugador.
- **Bonus Incluido:** Minimapa en tiempo real, colisiones mejoradas y texturas personalizadas.

---

## El Motor: Raycasting

El principio del Raycasting consiste en lanzar un rayo por cada columna vertical de la pantalla desde la posición del jugador. El rayo avanza por el mapa analizando las coordenadas hasta impactar contra un muro. 

A partir de la distancia euclidiana/perpendicular calculada, se determina la altura de la línea que debe dibujarse en pantalla: a menor distancia, más alta es la sección del muro.



---

## Arquitectura del Proyecto

El código fuente se encuentra estrictamente modularizado para cumplir con la norma de la escuela y garantizar la escalabilidad:

* **`src/parse/`**: Módulo encargado de la lectura del archivo `.cub`. Valida la existencia de las texturas, los colores del suelo/techo (RGB) y verifica mediante un algoritmo de **Flood Fill** que el mapa esté completamente cerrado por muros.
* **`src/raycasting/`**: El núcleo del motor. Calcula la intersección de los rayos con los ejes horizontales y verticales de la cuadrícula, renderiza los frames en un buffer secundario para evitar el parpadeo (*double buffering*) y proyecta las texturas.
* **`libft/`**: Librería personalizada con funciones auxiliares del sistema y utilidades de parsing como `get_next_line`.

---

## Características y Bonus Implementados

| Componente | Descripción Técnica |
| --- | --- |
| **DDA Algorithm** | Implementación del algoritmo *Digital Differential Analysis* para buscar colisiones de rayos de forma ultraeficiente. |
| **Manejo de Texturas** | Mapeo de texturas orientadas (Norte, Sur, Este, Oeste) en formato `.xpm` calculando el punto exacto de impacto del rayo. |
| **Minimapa** | Interfaz en una esquina de la pantalla que muestra el mapa 2D, la posición del jugador y su cono de visión en tiempo real. |
| **Sistema de Colisiones** | Prevención de traspaso de muros deslizando suavemente al jugador a lo largo de las paredes al colisionar. |

---

## Compilación y Uso

El proyecto compila bajo un entorno Linux/X11 utilizando un `Makefile` con flags estrictos (`-Wall -Wextra -Werror`).

### Requisitos previos (Linux)
Asegúrate de tener instaladas las librerías de desarrollo de X11:
```bash
sudo apt-get install libx11-dev libxext-dev

```

### Ejecución

```bash
# 1. Clonar y compilar el proyecto junto con la MiniLibX y Libft
make

# 2. Ejecutar el motor pasando un mapa válido como argumento
./cub3D maps/map1.cub

```

### Controles del Juego

* `W`, `A`, `S`, `D`: Movimiento del jugador (Adelante, Izquierda, Atrás, Derecha).
* `←` / `→` (Flechas): Rotación de la cámara.
* `ESC` o `Click en la X`: Cierre limpio del programa liberando el 100% de la memoria.
