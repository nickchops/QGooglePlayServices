director:startRendering()

require("helpers/Utility")
require("helpers/VirtualResolution")

--require("mobdebug").start() -- Uncomment for ZeroBrain IDE debuger support

appWidth = 640
appHeight = 960
virtualResolution:initialise{userSpaceW=appWidth, userSpaceH=appHeight}
screenWidth = virtualResolution:winToUserSize(director.displayWidth)
screenHeight = virtualResolution:winToUserSize(director.displayHeight)


dofile("SceneMainMenu.lua")
dofile("SceneGame.lua")

director:moveToScene(sceneMainMenu)

function shutDownApp()
    --terminate GPS here
    system:quit()
end
