var quat = quat || {};

quat.GameStateController = quat.StateController.extend({
    states: {
        /*
        When only the current solution progress is showing.
         */
        IDLE: null,

        GESTURING: null,
        /*
        The user has started swiping to the right to get to another menu.
         */
        SWIPING_RIGHT: null
    }
});

quat.ScreenStateController = quat.StateController.extend({
    states: {
        /*
        When the user is playing the vanilla game.
         */
        GAME: function(self) {
            var scene = self.gameScene,
                puzzleLayer = scene.puzzleLayer;

            self.currentLayer = puzzleLayer;
            puzzleLayer.setVisible(true);

            var game = scene.gameState,
                puzzle = game.getPuzzle(),
                indicator = puzzleLayer.textIndicatorLayer;

            indicator.stopAllActions();
            indicator.clearMessages();
            if (puzzle.isSpecial()) {
                puzzleLayer.textIndicatorLayer.addMessage(puzzle.getSpecialText().toUpperCase(), true);
            }

            puzzleLayer.solutionLayer.updateFromModel(game);
            scene.menuLayer.setVisible(false);
            scene.menuIcon.setVisible(true);
        },
        /*
        When the user is at the main menu.
         */
        MAIN_MENU: function(self) {
            var scene = self.gameScene,
                menuLayer = scene.menuLayer;
                menuIcon = scene.menuIcon;

            if (self.state == self.states.LOOK) {
                scene.applyThemeByName(scene.gameState.getUser().getTheme());
            }

            menuLayer.setVisible(true);
            scene.menuIcon.setVisible(false);
            self.currentLayer = menuLayer;
            scene.puzzleLayer.setVisible(false);
            scene.statsLayer.setVisible(false);
            scene.lookLayer.setVisible(false);
            scene.aboutLayer.setVisible(false);
            
        },
        LOOK: function(self) {
            var scene = self.gameScene,
                puzzleLayer = scene.puzzleLayer;

            var indicator = puzzleLayer.textIndicatorLayer;
            indicator.stopAllActions();
            indicator.clearMessages();

            // Set the current layer
            self.currentLayer = puzzleLayer;
            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            scene.puzzleLayer.setVisible(false);
            scene.lookLayer.setVisible(true);
            scene.menuIcon.setVisible(true);
            
            // Set up the puzzleLayer for LOOK changing
            scene.lookLayer.viewTheme(scene.gameState.getUser().getTheme());
        },
        STATS: function(self) {
            var scene = self.gameScene,
                statsLayer = self.gameScene.statsLayer;

            // Set the current layer
            self.currentLayer = statsLayer;

            statsLayer.updateData();
            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            scene.menuIcon.setVisible(true);
            statsLayer.setVisible(true);
            statsLayer.setOpacity(255);
        },
        ABOUT: function(self) {
            var scene = self.gameScene,
                aboutLayer = self.gameScene.aboutLayer;

            // Set the current layer
            self.currentLayer = aboutLayer;
            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            scene.menuIcon.setVisible(true);
            aboutLayer.setVisible(true);
            aboutLayer.setOpacity(255);
        },
        DEFAULT: function(self) {
            var scene = self.gameScene,
                defaultLayer = self.gameScene.defaultLayer;

            // Set the current layer
            self.currentLayer = defaultLayer;


            
            // Make the other ones invisible
            scene.menuLayer.setVisible(false);
            scene.menuIcon.setVisible(false);
            defaultLayer.setVisible(true);
            defaultLayer.setOpacity(255);
        },
    },

    init: function(gameScene) {
        this._super();
        this.gameScene = gameScene;
    }
});