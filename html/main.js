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