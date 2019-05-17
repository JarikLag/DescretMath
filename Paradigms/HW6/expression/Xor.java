package expression;

public class Xor extends AbstractBinaryOperator {
    public Xor(final TripleExpression first, final TripleExpression second) {
        super(first, second);
    }

    protected int calculate(final int first, final int second) {
        return first ^ second;
    }
}
