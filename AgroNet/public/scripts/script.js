
async function atualizarDados() {
    try {
        const resultado = await fetch('http://192.168.0.109/dados');
        const dados = await resultado.json();

        document.querySelector('#temperatura').textContent = dados.temperatura + ' °C';
        document.querySelector('#umidade').textContent = dados.umidade + ' %';
        document.querySelector('#luminosidade').textContent = dados.luminosidade + ' %';
        document.querySelector('#ip').textContent = "ESP8266 conectado no IP: " + dados.ip;

    } catch (error) {
        console.error('Erro ao buscar dados:', error);
    }
}

setInterval(atualizarDados, 2000);

atualizarDados();