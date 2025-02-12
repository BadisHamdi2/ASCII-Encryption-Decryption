const { SerialPort, ReadlineParser } = require('serialport')

const { createServer } = require("http");
const { Server } = require("socket.io");

const httpServer = createServer();
const io = new Server(httpServer, { 
    cors: {
        origin: "http://localhost:5173", // Allow requests from your frontend
        methods: ["GET", "POST"]
      }
});

const port = new SerialPort({ path:'COM9', baudRate:115200 })
var parser = new ReadlineParser()
port.pipe(parser)

parser.on('data', (data) => {
    
    data = data.trim(); // Remove extra whitespace and newlines

    if (!data) {
        console.log('Received empty data, skipping...');
        return; // Skip further processing for empty data
    }

    console.log(`Raw data: ${data}`);
    
    const values = data.split(',');

    // Check if we have the expected number of values
    if (values.length < 2) {
        console.log('Incomplete data packet, skipping...');
        return;
    }

    var val1 =parseInt(values[0]);
    var val2=parseInt(values[1]);
    var val3=parseInt(values[2]);
    var val4 =parseInt(values[3]);
    var val5=parseInt(values[4]);
    var val6=parseInt(values[5]);
    var val7 =parseInt(values[6]);
    var val8=parseInt(values[7]);

    console.log(`val1: ${val1}, val2: ${val2},val3: ${val3}, val4: ${val4},val5: ${val5}, val6: ${val6},val7: ${val7}, val8: ${val8} `);
    
    io.emit('sensor-data', { val1,val2,val3,val4,val5,val6,val7,val8});
    
});

io.on('connection', (socket) => {
    console.log('A client connected');
});

// Start the server on port 3000
httpServer.listen(3000, () => {
    console.log('Server is running on port 3000');
});

