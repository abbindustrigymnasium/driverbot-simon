import Aedes from "aedes"

// Store to store the broker state

let serverStore: Aedes | null = null;

export function setServerStore(server: Aedes | null): void {
 serverStore = server;
}

export function getServerStore(): Aedes | null {
 return serverStore;
}

export function clearServerStore(): void {
 serverStore = null;
}