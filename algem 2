import itertools

def read_matrix_from_file(file_path):
    """Читает матрицу из файла, где первая строка содержит размер матрицы."""
    with open(file_path, 'r') as file:
        n = int(file.readline().strip())  # Читаем размер матрицы
        matrix = []
        for _ in range(n):
            # Читаем строки матрицы и преобразуем их в список целых чисел
            row = list(map(int, file.readline().split()))
            matrix.append(row)
    return matrix

def determinant_leibniz(matrix):
    """Вычисляет определитель матрицы по комбинаторной формуле Лейбница."""
    n = len(matrix)
    permutations = list(itertools.permutations(range(n)))  # Генерируем все перестановки
    det = 0
    terms = []

    for perm in permutations:
        product = 1
        for i in range(n):
            # Умножаем элементы из каждой строки матрицы на элементы по перестановке
            product *= matrix[i][perm[i]]

        # Определяем знак текущего термина
        sign = (-1) ** sum(1 for i in range(n) for j in range(i + 1, n) if perm[i] > perm[j])
        term = f"{sign * product}" if sign > 0 else f"-{abs(sign * product)}"
        terms.append(term)

        det += sign * product  # Суммируем текущий термин к определителю

    print("\nОпределитель матрицы по комбинаторной формуле:")
    print(' + '.join(terms) + f' = {det}')  # Выводим все термины
    return det

def determinant_laplace(matrix):
    """Вычисляет определитель матрицы по рекурсивной формуле Лапласа."""
    n = len(matrix)

    def get_minor(matrix, row, col):
        """Получает минор матрицы, исключая заданную строку и столбец."""
        return [[matrix[i][j] for j in range(len(matrix)) if j != col]
                for i in range(len(matrix)) if i != row]

    # Выбор строки с максимальным количеством нулей
    max_zeros = -1
    best_index = 0
    for i in range(n):
        zeros_count = matrix[i].count(0)
        if zeros_count > max_zeros:
            max_zeros = zeros_count
            best_index = i

    print(f"\nРазложение определителя по строке {best_index + 1}:")
    det = 0
    terms = []

    for col in range(n):
        if matrix[best_index][col] != 0:
            sign = (-1) ** (best_index + col)
            minor_matrix = get_minor(matrix, best_index, col)  # Получаем минор
            # Рекурсивно вычисляем определитель минора
            minor_det = determinant_laplace(minor_matrix) if len(minor_matrix) > 1 else minor_matrix[0][0]
            term = sign * matrix[best_index][col] * minor_det
            det += term  # Суммируем прилагаемые к определителю термины

            terms.append(f"{matrix[best_index][col]} * Det(minor) = {term}")

    for term in terms:
        print(term)

    print(f"Определитель матрицы по рекурсивной формуле: {det}")
    return det

def determinant_gauss(matrix):
    """Вычисляет определитель матрицы методом Гаусса."""
    n = len(matrix)
    det = 1  # Изначально определитель равен 1
    sign_changes = 0  # Счетчик для изменений знака при перестановках строк

    for i in range(n):
        while True:  # Цикл для выбора ведущего элемента
            # Поиск ненулевого элемента с минимальным значением в текущем столбце
            min_row_index = None
            for r in range(i, n):
                if matrix[r][i] != 0:
                    if min_row_index is None or abs(matrix[r][i]) < abs(matrix[min_row_index][i]):
                        min_row_index = r

            # Если все элементы в текущем столбце равны 0, определитель равен 0
            if min_row_index is None:
                print("Определитель матрицы равен 0, так как все элементы в строке/столбце равны 0.")
                return 0

            # Перестановка строк, если найденный ведущий элемент не на своем месте
            if min_row_index != i:
                print(f"Перестановка строк {i + 1} и {min_row_index + 1}")
                matrix[i], matrix[min_row_index] = matrix[min_row_index], matrix[i]
                sign_changes += 1  # Увеличиваем счетчик изменений знака

            leading_element = matrix[i][i]  # Запоминаем ведущий элемент

            # Обнуление элементов ниже текущего ведущего элемента
            for j in range(i + 1, n):
                current_element = matrix[j][i]
                if current_element != 0 and leading_element != 0:
                    # Целочисленный коэффициент для вычитания
                    factor = current_element // leading_element  # Используем целочисленное деление
                    print(f"Из строки {j + 1} вычитаем {factor} * строку {i + 1}")

                    for k in range(i, n):
                        matrix[j][k] -= factor * matrix[i][k]  # Обновляем строку

            print(f"Матрица после обработки строки {i + 1}:")
            print_matrix(matrix)

            # Проверяем, является ли текущая строка с ведущим элементом корректной
            if all(matrix[j][i] == 0 for j in range(i + 1, n)):
                break  # Выход из цикла, если все элементы ниже равны 0

    # Подсчет определителя как произведение основных диагональных элементов
    final_determinant = 1
    for i in range(n):
        final_determinant *= matrix[i][i]  # Умножаем на главные диагональные элементы

    # Учитываем изменения знака из-за перестановок строк
    if sign_changes % 2 == 1:
        final_determinant *= -1

    # Выводим детерминант в требуемом формате
    determinant_formula = "*".join(str(matrix[i][i]) for i in range(n))
    print(f"Определитель матрицы по методу Гаусса: {det} * ({determinant_formula}) = {final_determinant}")

    return final_determinant  # Возвращаем определитель

def is_upper_triangular(matrix):
    """Проверка, является ли матрица верхней треугольной."""
    n = len(matrix)
    for i in range(n):
        for j in range(i + 1, n):
            if matrix[j][i] != 0:
                return False
    return True

def print_matrix(matrix):
    """Выводит матрицу в виде строк."""
    for row in matrix:
        print(' '.join(map(str, row)))

if __name__ == "__main__":
    import sys

    input_file = sys.argv[1]  # Получаем путь к файлу из аргументов командной строки

    # Читаем матрицу из файла
    A = read_matrix_from_file(input_file)
    print("Матрица А:")
    print_matrix(A)

    print("\nВычисление определителя матрицы А:\n")

    # Вычисляем определитель по различным методам
    print("\nКомбинаторная формула Лейбница:")
    print("Матрица А:")
    print_matrix(A)
    leibniz_det = determinant_leibniz(A)

    print("\nРекурсивная формула Лапласа:")
    print("Матрица А:")
    print_matrix(A)
    laplace_det = determinant_laplace(A)

    print("\nМетод Гаусса:")
    print("Матрица А:")
    print_matrix(A)
    gauss_det = determinant_gauss(A)
