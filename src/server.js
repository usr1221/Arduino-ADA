const express = require('express');
const app = express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);

app.use(express.json()); // Dla parsowania JSON w zapytaniach
app.use(express.static('../public')); // Serwowanie plików statycznych

app.get('/', (req, res) => {
  res.sendFile('index.html');
});

app.post('/api/alert', (req, res) => {
    const data = req.body; // Odbierz dane z zapytania
    io.emit('alert', data); // Wyślij dane do wszystkich podłączonych klientów
    res.status(200).send('Alert otrzymany');
});

io.on('connection', (socket) => {
  console.log('Nowy użytkownik podłączony');
  
  socket.on('disconnect', () => {
    console.log('Użytkownik rozłączony');
  });

  // Tutaj obsługa wiadomości od klientów
});

const PORT = 3000;
http.listen(PORT, () => {
  console.log(`Serwer działa na porcie ${PORT}`);
});


  