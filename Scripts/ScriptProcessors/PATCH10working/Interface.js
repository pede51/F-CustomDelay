Content.makeFrontInterface(600, 800);

// Global variable declarations
const var pb = Engine.createBroadcaster({
    "id": "Property Syncer",
    "colour": -1,
    "args": ["component", "value"] // Parameters for the listeners
});

// Array of knob and label pairs
const var knobLabelPairs = [
    { knob: "knob1", label: "text1" }, // Regular knob
    { knob: "knob2", label: "text2" }, // Tempo sync knob
    { knob: "knob3", label: "text3" },
    { knob: "knob4", label: "text4" },
    { knob: "knob5", label: "text5" },
    { knob: "knob6", label: "text6" }
];

// Define variables for the value callback
var knobId; 
var labelId;
var label;
var initialValue;

// Function to round a number to a specific number of decimal places
function roundToDecimals(value, decimals) {
    var factor = Math.pow(10, decimals);
    return Math.round(value * factor) / factor; // Round the value
}

// Function to map knob values to tempo sync values based on your provided mappings
function mapTempoValue(value) {
    // Define your mapping for knob2's range (0 to 18)
    var tempoValues = [
        "1/1", "1/2D", "1/2", "1/2t",
        "1/4d", "1/4", "1/4t", "1/8d",
        "1/8", "1/8t", "1/16d", "1/16",
        "1/16t", "1/32D", "1/32", "1/32t",
        "1/64", "1/64", "1/64t"
    ];
    
    // Map value to tempo value based on knob2's position
    if (value >= 0 && value < tempoValues.length) {
        return tempoValues[value]; // Adjust for array indexing
    }
    return ""; // Return empty if out of bounds
}

// Define the value callback function
function valueCallback(component, value) {
    knobId = component.getId();
    labelId = knobId.replace("knob", "text"); // Change knob name to label name
    label = Content.getComponent(labelId); // Get the corresponding label

    if (label !== null) {
        var displayedValue;
        
        // Check if the knob is the tempo sync knob
        if (knobId === "knob2") {
            displayedValue = mapTempoValue(Math.floor(value)); // Get the mapped tempo value
        } else {
            displayedValue = roundToDecimals(value, 2); // Round to 2 decimal places for other knobs
        }
        
        label.set("text", displayedValue); // Update label text
    }
}

// Set up the broadcaster and listeners for each knob
function setupKnobListeners() {
    for (var i = 0; i < knobLabelPairs.length; i++) {
        var pair = knobLabelPairs[i];

        // Attach broadcaster to knob
        pb.attachToComponentValue(pair.knob, { "id": pair.knob }); // Adding id to metadata

        // Add listener for value changes
        pb.addListener(
            { "id": pair.knob + "Listener" }, // Unique ID for this listener
            { "id": pair.knob + " metadata" }, // Metadata with at least an id property
            valueCallback // Function to call when the value changes
        );

        // Set initial label text
        var knob = Content.getComponent(pair.knob);
        if (knob !== null) {
            initialValue = knob.getValue(); // Get the initial value
            label = Content.getComponent(pair.label);
            if (label !== null) {
                var roundedInitialValue = (knobId === "knob2") ? mapTempoValue(Math.floor(initialValue)) : roundToDecimals(initialValue, 2);
                label.set("text", roundedInitialValue); // Set initial text with appropriate formatting
            }
        }
    }
}

// Call the setup function to initialize everything
setupKnobListeners();



//ui colors
	const laf = Engine.createGlobalScriptLookAndFeel();
	
	
	laf.registerFunction("drawRotarySlider", function(g,obj){
		
		var a = obj.area;
		
		g.setColour(obj.bgColour);
		g.fillEllipse(a);
		
		g.setColour(obj.itemColour1);
		g.fillEllipse([10, 10, a[2] - 20, a[3] - 20]);
		
		var start = 2.5;
		var end = start * 2 * obj.valueNormalized - start;
		
		g.rotate(end, [a[2] / 2, a[3] /2 ]);	
		
		g.setColour(obj.itemColour2);
		g.fillRoundedRectangle([a[2] / 2 - 8 / 2 ,8 ,  8, 40], 5);
		
		
		

		
	} )
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
 