import pygame
import ctypes
import os
import sys

# --- ВАЖНО: ПРОВЕРКА ПУТИ ---
# Укажите путь туда, где вы только что скомпилировали DLL
dll_path = r"C:\Users\user\source\repos\wrc\Wrc.dll"

if not os.path.exists(dll_path):
    print(f"\n!!! ОШИБКА: Файл не найден !!!")
    print(f"Python ищет здесь: {dll_path}")
    print("Проверьте, правильно ли указан путь и скомпилирован ли файл.\n")
    sys.exit()

try:
    # Загружаем библиотеку
    lib = ctypes.CDLL(dll_path)
    print("Библиотека успешно загружена!")
except OSError as e:
    print(f"\n!!! ОШИБКА ЗАГРУЗКИ DLL !!!")
    print(f"Детали: {e}")
    print("Возможные причины:")
    print("1. Вы не скомпилировали с флагом -static")
    print("2. У вас 32-битный компилятор g++, а Python 64-битный")
    sys.exit()

# --- НАСТРОЙКИ ---
CELL_SIZE = 40       # Размер клетки в пикселях
MAP_SIZE = 16        # Размер карты (16x16)
WINDOW_SIZE = CELL_SIZE * MAP_SIZE
FPS = 1             # Скорость игры (кадров в секунду)

# Цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
RED = (200, 50, 50)    # Волк
GREEN = (50, 200, 50)  # Капуста
BLUE = (50, 50, 200)   # Заяц
YELLOW = (255, 255, 0) # Выделение

# --- ЗАГРУЗКА DLL ---
lib = ctypes.CDLL(r'C:\Users\user\source\repos\wrc\Wrc.dll')

# Структура, совпадающая с C++ ExportData
class ExportData(ctypes.Structure):
    _fields_ = [
        ("obj_ptr", ctypes.c_void_p),
        ("type", ctypes.c_int),
        ("x", ctypes.c_int),
        ("y", ctypes.c_int),
        ("stamina", ctypes.c_int)
    ]

# Настройка типов аргументов
lib.create_map.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
lib.create_map.restype = ctypes.c_void_p

lib.make_step.argtypes = [ctypes.c_void_p]
lib.if_game_over.argtypes = [ctypes.c_void_p] 
lib.if_game_over.restype = ctypes.c_int

lib.del_map.argtypes = [ctypes.c_void_p]

# get_snapshot
lib.get_snapshot.argtypes = [ctypes.c_void_p, ctypes.POINTER(ExportData), ctypes.c_int]
lib.get_snapshot.restype = ctypes.c_int

# Функции управления
lib.give_s.argtypes = [ctypes.c_void_p, ctypes.c_int]
lib.move_on.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_void_p, ctypes.c_int]


# --- ФУНКЦИИ ---
# Получаем путь к папке, где лежит сам скрипт
script_dir = os.path.dirname(os.path.abspath(__file__))
# Склеиваем путь к папке и имя файла
file_path = os.path.join(script_dir, "input.txt")

import os

def load_config():
    # Эта магия находит путь к папке, где лежит сам файл wrc.py
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Склеиваем путь к папке и имя файла
    full_path = os.path.join(script_dir, "input.txt")

    print(f"Ищу файл конфигурации здесь: {full_path}") # Для проверки

    try:
        with open(full_path, "r") as f:
            line = f.readline()
            # Проверяем, не пустой ли файл
            if not line:
                print("Файл пустой! Берем стандартные значения.")
                return 2, 6, 2
            
            w, r, c = map(int, line.split())
            return w, r, c
    except FileNotFoundError:
        print(f"ФАЙЛ НЕ НАЙДЕН по пути: {full_path}")
        print("Проверьте, что input.txt лежит в той же папке, что и wrc.py")
        return 2, 6, 2
    except Exception as e:
        print(f"Ошибка чтения данных: {e}. Берем стандарт.")
        return 2, 6, 2

def draw_grid(screen):
    for x in range(0, WINDOW_SIZE, CELL_SIZE):
        pygame.draw.line(screen, GRAY, (x, 0), (x, WINDOW_SIZE))
    for y in range(0, WINDOW_SIZE, CELL_SIZE):
        pygame.draw.line(screen, GRAY, (0, y), (WINDOW_SIZE, y))

def draw_objects(screen, objects, selected_ptr):
    font = pygame.font.SysFont(None, 24)
    
    for obj in objects:
        # Координаты для рисования
        cx = obj.x * CELL_SIZE + CELL_SIZE // 2
        cy = obj.y * CELL_SIZE + CELL_SIZE // 2
        radius = CELL_SIZE // 2 - 4

        color = BLACK
        if obj.type == 0: color = GREEN  # Капуста
        elif obj.type == 1: color = BLUE   # Заяц
        elif obj.type == 2: color = RED    # Волк

        # Если объект выбран - рисуем желтый ободок
        if obj.obj_ptr == selected_ptr:
            pygame.draw.circle(screen, YELLOW, (cx, cy), radius + 3)

        pygame.draw.circle(screen, color, (cx, cy), radius)
        
        # Рисуем стамину (опционально)
        text = font.render(str(obj.stamina), True, WHITE)
        screen.blit(text, (cx - 5, cy - 8))

def get_py_objects(mapp):
    # Создаем массив структур (буфер)
    max_objs = 100
    BufferArray = ExportData * max_objs
    buffer = BufferArray()
    
    # Запрашиваем данные у C++
    count = lib.get_snapshot(mapp, buffer, max_objs)
    
    # Конвертируем в удобный список Python
    py_list = []
    for i in range(count):
        # Копируем данные, чтобы они не перезаписались
        data = ExportData()
        data.obj_ptr = buffer[i].obj_ptr
        data.type = buffer[i].type
        data.x = buffer[i].x
        data.y = buffer[i].y
        data.stamina = buffer[i].stamina
        py_list.append(data)
        
    return py_list

# --- MAIN ---
def main():
    pygame.init()
    screen = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE + 50)) # +50 пикселей для текста внизу
    pygame.display.set_caption("Ecosystem Simulation")
    clock = pygame.time.Clock()
    font = pygame.font.SysFont(None, 30)

    # 1. Загрузка параметров
    w, r, c = load_config()
    print(f"Creating map: Wolfs={w}, Rabbits={r}, Coles={c}")
    
    # 2. Создание карты
    mapp = lib.create_map(w, r, c)
    
    running = True
    paused = False
    game_over_msg = ""
    selected_obj_ptr = None # Указатель на выбранного зверя

    # Список объектов для отрисовки
    current_objects = get_py_objects(mapp)

    while running:
        # 1. Обработка событий
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    paused = not paused
                
                # Управление во время паузы
                if paused and selected_obj_ptr is not None:
                    # Кормление (F)
                    if event.key == pygame.K_f:
                        print("Feeding object...")
                        lib.give_s(ctypes.c_void_p(selected_obj_ptr), 5)
                        current_objects = get_py_objects(mapp) # Обновляем картинку

                    # Движение стрелками (Стрелки)
                    dx, dy = 0, 0
                    if event.key == pygame.K_UP: dy = -1
                    elif event.key == pygame.K_DOWN: dy = 1
                    elif event.key == pygame.K_LEFT: dx = -1
                    elif event.key == pygame.K_RIGHT: dx = 1
                    
                    if dx != 0 or dy != 0:
                        print(f"Manual move: {dx}, {dy}")
                        # mode=0 -> принудительное движение
                        lib.move_on(ctypes.c_void_p(selected_obj_ptr), dx, dy, mapp, 0)
                        current_objects = get_py_objects(mapp) # Обновляем картинку

            elif event.type == pygame.MOUSEBUTTONDOWN and paused:
                # Выбор объекта мышкой
                mx, my = pygame.mouse.get_pos()
                grid_x = mx // CELL_SIZE
                grid_y = my // CELL_SIZE
                
                selected_obj_ptr = None # Сброс
                for obj in current_objects:
                    if obj.x == grid_x and obj.y == grid_y:
                        selected_obj_ptr = obj.obj_ptr
                        print(f"Selected object type {obj.type} at {obj.x},{obj.y}")
                        break

        # 2. Логика игры
        if not paused and not game_over_msg:
            lib.make_step(mapp)
            current_objects = get_py_objects(mapp) # Обновляем список после хода
            
            # Проверка конца игры
            status = lib.if_game_over(mapp)
            if status == 0: # 0 означает true (конец) в вашей логике
                game_over_msg = "GAME OVER!" # Можно уточнить кто выиграл, если вернуть код из if_game_over
                paused = True # Останавливаем игру

        # 3. Отрисовка
        screen.fill(WHITE)
        draw_grid(screen)
        draw_objects(screen, current_objects, selected_obj_ptr)
        
        # Рисуем панель статуса внизу
        pygame.draw.rect(screen, BLACK, (0, WINDOW_SIZE, WINDOW_SIZE, 50))
        status_text = f"Paused: {paused} | Selected: {'Yes' if selected_obj_ptr else 'No'}"
        if game_over_msg:
            status_text = game_over_msg
            
        txt_surf = font.render(status_text, True, WHITE)
        screen.blit(txt_surf, (10, WINDOW_SIZE + 15))

        pygame.display.flip()
        clock.tick(FPS)

    lib.del_map(mapp)
    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()