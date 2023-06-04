#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Definici�n de la funci�n de activaci�n (en este caso, la funci�n escal�n)
int activationFunction(double sum) {
    return (sum < 0) ? 0 : 1;
}

// Clase para representar una neurona artificial
class Neuron {
private:
    std::vector<double> weights; // Pesos sin�pticos
    double bias; // Umbral
    double learningRate; // Factor de aprendizaje

public:
    Neuron(int numInputs, double learningRate) : learningRate(learningRate) {
        // Inicializaci�n aleatoria de los pesos sin�pticos y el umbral
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < numInputs; ++i) {
            weights.push_back(static_cast<double>(std::rand()) / RAND_MAX);
        }
        bias = static_cast<double>(std::rand()) / RAND_MAX;
    }

    // Funci�n para calcular la salida de la neurona
    int calculateOutput(const std::vector<double>& inputs) {
        double sum = bias;
        for (int i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * weights[i];
        }
        return activationFunction(sum);
    }

    // Funci�n para ajustar los pesos sin�pticos y el umbral seg�n el resultado obtenido
    void adjustWeights(const std::vector<double>& inputs, int target) {
        int output = calculateOutput(inputs);
        double error = output - target;
        for (int i = 0; i < weights.size(); ++i) {
            weights[i] += learningRate * error * inputs[i];
        }
        bias += learningRate * error;
    }

    // Funci�n para obtener los par�metros aprendidos por la neurona
    std::vector<double> getLearnedParameters() const {
        return weights;
    }
};

int main() {
    setlocale(LC_ALL, "");

    std::vector<std::string> inputLabels = { "Experiencia", "Habilidades", "Educaci�n", "Idiomas" };

    int numInputs = inputLabels.size(); // N�mero de entradas
    double learningRate; // Factor de aprendizaje

    // Obtener el factor de aprendizaje de entrada
    std::cout << "Haga el ingreso del factor de aprendizaje: ";
    std::cin >> learningRate;

    Neuron neuron(numInputs, learningRate);

    // Entrada de datos
    std::vector<double> inputs(numInputs);
    for (int i = 0; i < numInputs; ++i) {
        std::cout << "Ingrese la puntuaci�n de " << inputLabels[i] << ": ";
        std::cin >> inputs[i];
    }

    // Etiqueta de clase (1 para apto, 0 para no apto)
    int target;
    std::cout << "Ingrese la etiqueta de clase (1 para apto, 0 para no apto): ";
    std::cin >> target;

    // Calcular la salida de la neurona
    int output = neuron.calculateOutput(inputs);

    // Verificar si la predicci�n es correcta
    bool isPredictionCorrect = (output == target);
    std::cout << "El candidato es " << (isPredictionCorrect ? "apto" : "no apto") << " para el puesto." << std::endl;

    // Mostrar los par�metros aprendidos por la neurona
    std::vector<double> learnedParameters = neuron.getLearnedParameters();
    std::cout << "Par�metros aprendidos:\n";
    for (int i = 0; i < learnedParameters.size(); ++i) {
        std::cout << "Peso " << i + 1 << ": " << learnedParameters[i] << std::endl;
    }

    system("pause");
    return 0;
}
