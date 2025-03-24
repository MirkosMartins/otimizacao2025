//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

import kotlin.math.sqrt
import kotlin.random.Random

    fun main() {
        // Gerar dois pontos aleatórios no plano (x, y)
        val x1 = Random.nextInt(1, 11)
        val y1 = Random.nextInt(1, 11)
        val x2 = Random.nextInt(1, 11)
        val y2 = Random.nextInt(1, 11)

        // Calcular a distância entre os pontos
        val distancia = sqrt(((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)).toDouble())

        // Exibir os resultados
        println("Ponto 1: ($x1, $y1)")
        println("Ponto 2: ($x2, $y2)")
        println("Distância entre os pontos: $distancia")
    }
