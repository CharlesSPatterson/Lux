ig.module(
    'game.entities.object'
)
    .requires(
    'impact.entity'
)
    .defines(function(){
        EntityObject = ig.Entity.extend({

            collides: ig.Entity.COLLIDES.FIXED,
            health: 20,

            type: ig.Entity.TYPE.B,
            checkAgainst: ig.Entity.TYPE.BOTH,

            sector: 0,
            room: 0,

            direction: 'downright',

            init: function( x, y, settings ) {
                this.parent( x, y, settings );

                this.direction = settings.direction;
                this.room = settings.room;
            },

            update: function() {

                this.zIndex = Math.floor(this.pos.y) + this.getSector()*10000;

                switch(this.direction) {
                    case 'upleft':
                        this.currentAnim = this.anims.upleft;
                        break;
                    case 'downleft':
                        this.currentAnim = this.anims.downleft;
                        break;
                    case 'upright':
                        this.currentAnim = this.anims.upright;
                        break;
                    case 'downright':
                        this.currentAnim = this.anims.downright;
                        break;
                    default:
                        break;
                }

                // move
                this.parent();
            },

            getSector: function() {
                if ((this.pos.x + this.offset.x + this.size.x/2) - (this.pos.y + this.offset.y + this.size.y) >= 557) {
                    if ((this.pos.x + this.offset.x + this.size.x/2) + (this.pos.y + this.offset.y + this.size.y) <= 4361) {
                        return 0;
                    } else {
                        return 1;
                    }
                } else if ((this.pos.x + this.offset.x + this.size.x/2) - (this.pos.y + this.offset.y + this.size.y) >= 48) {
                    if ((this.pos.x + this.offset.x + this.size.x/2) + (this.pos.y + this.offset.y + this.size.y) <= 4361) {
                        return 2;
                    } else {
                        return 3;
                    }
                } else if ((this.pos.x + this.offset.x + this.size.x/2) - (this.pos.y + this.offset.y + this.size.y) >= -450) {
                    if ((this.pos.x + this.offset.x + this.size.x/2) + (this.pos.y + this.offset.y + this.size.y) <= 4361) {
                        return 4;
                    } else {
                        return 5;
                    }
                } else if ((this.pos.x + this.offset.x + this.size.x/2) - (this.pos.y + this.offset.y + this.size.y) >= -954) {
                    if ((this.pos.x + this.offset.x + this.size.x/2) + (this.pos.y + this.offset.y + this.size.y) <= 4361) {
                        return 6;
                    } else {
                        return 7;
                    }
                } else {
                    if ((this.pos.x + this.offset.x + this.size.x/2) + (this.pos.y + this.offset.y + this.size.y) <= 4361) {
                        return 8;
                    } else {
                        return 9;
                    }
                }
            }
        });
    });