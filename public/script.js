const socket = io();
        const alertsContainer = document.getElementById('alerts');

        socket.on('alert', function(data) {
            const alertBox = document.createElement('div');
            alertBox.className = 'alert-box';
            const icon = document.createElement('img');
            const number = data.number;
            const name = data.name;
            const text = document.createElement('p');
            const content = document.createElement('div');
            content.className = 'alert-content';
            switch (number){
                case 1:
                    text.textContent = `${name}: Jestem głodny`;
                    icon.src = '/static/jedzenie.png';
                    break;
                case 2:
                    text.textContent = `${name}: Chcę pić`;
                    icon.src = '/static/picie.png';
                    break;
                case 3:
                    text.textContent = `${name}: Potrzebuję do toalety`;
                    icon.src = '/static/toaleta.png';
                    break;
                case 4:
                    text.textContent = `${name}: Potrzebuję pomocy`;
                    icon.src = '/static/pomoc.png';
                    break;
                case 5:
                    text.textContent = `${name}: Chcę się pobawić`;
                    icon.src = '/static/zabawa.png';
                    break;
                case 6:
                    text.textContent = `${name}: Chcę iść na spacer`;
                    icon.src = '/static/spacer.png';
                    break;
                case 7:
                    text.textContent = `${name}: Coś mnie boli`;
                    icon.src = '/static/bol.png';
                    break;
                case 8:
                    text.textContent = `${name}: Stresuję się`;
                    icon.src = '/static/stres.png';
                    break;
                case 9:
                    text.textContent = `${name}: Jest za głośno`;
                    icon.src = '/static/halas.png';
                    break;
                default:
                    console.log('Invalid number');
                    break;

            }

        content.appendChild(icon);
        content.appendChild(text);
        alertBox.appendChild(content);
        
        const checklistButton = document.createElement('button');
        checklistButton.textContent = '✔'; 
        checklistButton.className = 'checklist-btn'; 
        alertBox.appendChild(checklistButton);

        checklistButton.addEventListener('click', function() {
        alertBox.style.opacity = 0;
        alertBox.addEventListener('transitionend', function() {
            alertsContainer.removeChild(alertBox);
            });
        });
         alertsContainer.appendChild(alertBox);

            alertBox.style.opacity = 0;
            window.setTimeout(() => {
                alertBox.style.opacity = 1;
            }, 10);
        });