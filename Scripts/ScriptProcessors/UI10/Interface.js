Content.makeFrontInterface(600, 600);

const laf = Engine.createGlobalScriptLookAndFeel();

laf.registerFunction("drawRotarySlider", function(g, obj) {
    var a = obj.area;
    var centerX = a[2] / 2;
    var centerY = a[3] / 2;
    
    // Background circle
    g.setColour(obj.bgColour);
    g.fillEllipse(a);

    // Inner circle (knob body)
    g.setColour(obj.itemColour1);
    g.fillEllipse([10, 10, a[2] - 20, a[3] - 20]);

    // Rotation calculation for the pointer
    var start = 2.5; // Start angle
    var end = start * 2 * obj.valueNormalized - start;

    g.rotate(end, [a[2] / 2, a[3] / 2]);

    // Draw the pointer
    g.setColour(obj.itemColour2);
    g.fillRoundedRectangle([a[2] / 2 - 8 / 2, 8, 8, 40], 5);

    // Reset rotation for the text
    g.resetTransform();

    // Draw the value as text under the knob
    var valueText = "Value: " + Math.round(obj.value); // Display knob value
    g.setColour(0xFFFFFFFF); // White color for the text
    g.setFont("Arial", 16.0);
    
    var textWidth = g.getStringWidth(valueText);
    var textX = centerX - textWidth / 2;
    var textY = a[3] + 20; // Position text below the knob
    
    g.drawText(valueText, [textX, textY, textWidth, 20], "left");
});

function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
 