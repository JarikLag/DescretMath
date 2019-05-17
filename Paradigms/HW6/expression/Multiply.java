package expression;

public class Multiply extends AbstractBinaryOperator {
    public Multiply(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first * second;
    }
}
