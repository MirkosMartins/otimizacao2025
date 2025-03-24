import kotlin.math.*
import kotlin.random.Random

fun main() {
    // Gerar pontos aleatórios
    val x1 = Random.nextInt(1, 11)
    val y1 = Random.nextInt(1, 11)
    val x2 = Random.nextInt(1, 11)
    val y2 = Random.nextInt(1, 11)

    // Calcular inclinação da reta
    val a = (y2 - y1).toDouble() / (x2 - x1).toDouble()

    // Calcular a interceptação da reta
    val b = y1 - a * x1

    // Exibir equação da reta
    println("Ponto 1: ($x1, $y1)")
    println("Ponto 2: ($x2, $y2)")
    println("A equação da reta é:")
    println("y = ${a}x + $b")
}
