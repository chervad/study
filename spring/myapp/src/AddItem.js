import React, { Component } from 'react';
import SkyLight from 'react-skylight';

class AddItem extends Component {
    constructor(props) {
        super(props);
    }

    addItem = () => {
        const item = {product: this.state.product,
            amount: this.state.amount};
        this.props.additem(item);
        this.addform.hide();
    }

    handleChange = (e) => {
        this.setState({[e.target.name]: e.target.value});
    }

    render() {
        return (
            <div>
                <section>
                    <button onClick={() => this.addform.show()}>Add item</button>
                </section>
                <SkyLight hide OnOverlayClicked  ref={ref => this.addform = ref} title="Add item">
                    <input type="text" name="product" onChange={this.handleChange} placeholder="product" /><br />
                    <input type="text" name="amount" onChange={this.handleChange} placeholder="amount" /><br />
                    <button onClick={this.addItem}>Add</button>
                </SkyLight>
            </div>
        );
    }
}

export default AddItem;
