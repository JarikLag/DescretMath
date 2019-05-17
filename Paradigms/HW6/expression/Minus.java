package expression;

public class Minus extends AbstractUnaryOperator {
    public Minus(final TripleExpression operand) {
        super(operand);
    }

    protected int calculate(final int operand) {
        return -operand;
    }
}
