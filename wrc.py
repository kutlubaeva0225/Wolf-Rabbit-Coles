import ctypes

# Загружаем библиотеку
lib = ctypes.CDLL(r'C:\Users\user\source\repos\wrc\wrc.dll')

# Определяем типы аргументов и возвращаемых значений
lib.create_map.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
lib.create_map.restype = ctypes.c_void_p

lib.m_print.argtypes = [ctypes.c_void_p]
lib.make_step.argtypes = [ctypes.c_void_p]
lib.del_map.argtypes = [ctypes.c_void_p]
mapp = lib.create_map(3, 2, 1)
for step in range(10):  # 10 шагов
    lib.make_step(mapp)
    lib.m_print(mapp)

lib.del_map(mapp)
exit()