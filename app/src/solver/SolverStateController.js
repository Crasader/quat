var quat = quat || {};
quat.solver = quat.solver || {};

/**
 * Handles all transitions between states.
 */
quat.solver.SolverStateController = function(puzzleScene) {
	// Grab all the references to things we need from puzzleScene
	this.quatGame = puzzleScene.quatGame;
	this.backgroundLayer = puzzleScene.backgroundLayer;
    this.solutionLayer = puzzleScene.solutionLayer;
    this.chooseLetterLayer = puzzleScene.chooseLetterLayer;
    this.gameBounds = puzzleScene.gameBounds;

    // The enumeration of all possible states for the solver GUI.
    this.states = {
        /*
        When only the current solution progress is showing.
         */
        IDLE: 0,
        /*
        When the user clicked on one of the letters in the current word,
        but has not dragged out of the current word yet.
         */
        CHOOSING_LETTER: 1,
        /*
        The user has dragged out of the current word (selecting a new
        letter) and has stayed in a single column. The letter chooser is still
        tied to the mouse.
         */
        CHANGING_LETTER_DRAG: 2,
        /*
        The user has stopped dragging, but the letter chooser is still visible
        and is in the place they left it. They can either tap on the letter to
        enter it into the solution or drag again.
         */
        CHANGING_LETTER_NODRAG: 3,
        /*
        The user started dragging in the solution space outside of the current
        word.
         */
        GESTURING: 4,
        /*
        The user has started swiping to the left to erase a word.
         */
        ERASING_WORD: 5,
        /*
        The user has started swiping to the right to get to the main menu.
         */
        SWIPING_TO_MENU: 6
    };


    // Sets the current state to IDLE
    this.state = this.states.IDLE;

    // Setting this to true prints every state change
    this.developer = false;

    var states = this.states;
    var stateToText = function(state) {
        var keys = Object.keys(states);
        return keys[state];
    }

    this.setState = function(state) {
        if (this.developer) {
            console.log(stateToText(this.state) + "->" + stateToText(state));
        }
        this.state = state;
    };

    // Records the previous y offset of the last drag action
    this.previousOffset = 0;
}

quat.solver.SolverStateController.prototype.IDLE = function() {
	if ((this.state == this.states.CHANGING_LETTER_NODRAG) ||
		(this.state == this.states.CHOOSING_LETTER)) {
		this.chooseLetterLayer.setVisible(false);
	}
    this.solutionLayer.updateFromModel(this.quatGame);
	this.setState(this.states.IDLE);
};

quat.solver.SolverStateController.prototype.CHOOSING_LETTER = function(column) {
	// Move the letter chooser to its proper location
	this.chooseLetterLayer.x = (column * (this.gameBounds.width / 4)) + this.gameBounds.x;
    this.chooseLetterLayer.setBaseLetter(this.quatGame.getCurrentWord()[column]);
    this.chooseLetterLayer.setVisible(true);

	this.setState(this.states.CHOOSING_LETTER);
};


quat.solver.SolverStateController.prototype.CHANGING_LETTER_DRAG = function() {
	this.setState(this.states.CHANGING_LETTER_DRAG);
};

quat.solver.SolverStateController.prototype.CHANGING_LETTER_NODRAG = function() {
	this.setState(this.states.CHANGING_LETTER_NODRAG);
};

quat.solver.SolverStateController.prototype.GESTURING = function() {
    this.setState(this.states.GESTURING);
};

quat.solver.SolverStateController.prototype.ERASING_WORD = function() {
    this.setState(this.states.ERASING_WORD);
};

quat.solver.SolverStateController.prototype.SWIPING_TO_MENU = function() {
    this.setState(this.states.SWIPING_TO_MENU);
};