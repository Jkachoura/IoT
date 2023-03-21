# Deelopdracht 1 - Netwerk en Security Vervolg
- Jaouad Kachoura
## Inhoudsopgave

- [Installatie](#installatie)
    - [Benodigdheden](#benodigdheden)
    - [Building](#building)

## Installatie

### Benodigdheden
Installeer de volgende benodigheden als het nodig is

- [Docker](https://www.docker.com/products/docker-desktop/) 


### Building
1. Start Docker Desktop op.

2. Treedt de folder binnen waar docker-compose.yml zit en voer de volgende commando uit in je terminal:
```bash
$ docker compose up -d
```

3. Nu kan je 2 of meer webbrowsers openen op https://localhost en als je een bericht verzend op 1 van de webbrowsers is het ook te zien op de andere.

**Note:** Wanneer je de pagina refreshed wordt er een nieuwe client gegenereerd, dus de messages die je aan het versturen was of ontvangen hebt worden gewist.
