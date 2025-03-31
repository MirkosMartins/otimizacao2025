void main(List<String> args) {
  List<int> a = [4, 0];
  List<int> b = [0, -2];

  List<int> c = [0, 1];
  List<int> d = [1, 0];

  List<double>? intersection = encontrarIntersecao(a, b, c, d);

  if (intersection != null) {
    print('As retas se cruzam no ponto: (${intersection[0]}, ${intersection[1]})');
  } else {
    print('As retas não se cruzam.');
  }
}

List<double>? encontrarIntersecao(List<int> a, List<int> b, List<int> c, List<int> d) {
  int det = (b[0] - a[0]) * (d[1] - c[1]) - (b[1] - a[1]) * (d[0] - c[0]);

  if (det == 0) {
    return null;
  }

  double t = ((c[0] - a[0]) * (d[1] - c[1]) - (c[1] - a[1]) * (d[0] - c[0])) / det;

  double px = a[0] + t * (b[0] - a[0]);
  double py = a[1] + t * (b[1] - a[1]);
  return [px, py];
}