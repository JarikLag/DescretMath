package parser;

import expression.*;
import myExceptions.*;

public class ExpressionParser implements Parser {
    private Tokenizer myTokenizer;

    private TripleExpression unary() throws ParsingException {
        TripleExpression res;
        switch (myTokenizer.getNextToken()) {
            case NUMBER:
                res = new Const(myTokenizer.getValue());
                myTokenizer.getNextToken();
                break;
            case VARIABLE:
                res = new Variable(myTokenizer.getName());
                myTokenizer.getNextToken();
                break;
            case MINUS:
                res = new CheckedNegate(unary());
                break;
            case LOG10:
                res = new CheckedLog(unary(), new Const(10));
                break;
            case POW10:
                res = new CheckedPow(new Const(10), unary());
                break;
            case OPEN_BRACE:
                int pos = myTokenizer.getInd();
                res = addSub();
                if (myTokenizer.getCurrentToken() != Token.CLOSE_BRACE) {
                    throw new MissingClosingParenthesisException(myTokenizer.getExpression(), pos - 1);
                }
                myTokenizer.getNextToken();
                break;
            default:
                throw new ParsingException("Incorrect expression" + "\n" + myTokenizer.getExpression());
        }
        return res;
    }


    private TripleExpression mulDiv() throws ParsingException {
        TripleExpression res = unary();
        do {
            switch (myTokenizer.getCurrentToken()) {
                case MUL:
                    res = new CheckedMultiply(res, unary());
                    break;
                case DIV:
                    res = new CheckedDivide(res, unary());
                    break;
                default:
                    return res;
            }
        } while (true);
    }

    private TripleExpression addSub() throws ParsingException {
        TripleExpression res = mulDiv();
        do {
            switch (myTokenizer.getCurrentToken()) {
                case ADD:
                    res = new CheckedAdd(res, mulDiv());
                    break;
                case SUB:
                    res = new CheckedSubtract(res, mulDiv());
                    break;
                default:
                    return res;
            }
        } while (true);
    }

    public TripleExpression parse(final String s) throws ParsingException {
        myTokenizer = new Tokenizer(s);
        return addSub();
    }
}
