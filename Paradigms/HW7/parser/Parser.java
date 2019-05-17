package parser;

import expression.TripleExpression;
import myExceptions.ParsingException;

public interface Parser {
    TripleExpression parse(String expression) throws ParsingException;
}
