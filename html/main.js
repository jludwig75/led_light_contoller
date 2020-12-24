const app = Vue.createApp({
    data() {
        return {
            channels: []
        }
    },
    methods: {
        gotChannels(channelList) {
            this.channels = []
            for (channelNumber of channelList) {
                // Ignore the mode in the main script
                this.channels.push(parseInt(channelNumber));
            }
        }
    },
    mounted () {
        axios.
            get('/channels').
            then(response => this.gotChannels(response.data)).
            catch(error => console.log('Failed to get channel list: ' + error));
    }
})