let clientStore: any | null = null;

export function setClientStore(client : any | null): void {
 clientStore = client;
}

export function getClientStore(): any | null {
 return clientStore;
}

export function clearClientStore(): void {
 clientStore = null;
}