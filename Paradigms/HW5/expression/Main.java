package expression;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int x = sc.nextInt();
        AnyExpression exp = new Add(
                new Subtract(
                        new Multiply(
                                new Variable("x"),
                                new Variable("x")),
                        new Multiply(
                                new Variable("x"),
                                new Const(2))),
                new Const(1));
        System.out.println(exp.evaluate(x));
    }
}
